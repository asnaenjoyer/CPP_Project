#include "ExpenseManager.hpp"

#include <algorithm>
#include <iterator>
#include <fstream>

#include <nlohmann/json.hpp>

unsigned int ExpenseManager::nextTransactionId = 1;
unsigned int ExpenseManager::nextCategoryId = 1;

void ExpenseManager::addTransaction(unsigned int categoryId, std::int64_t amountMinorUnits,
                                    const std::string& name, TransactionType type,
                                    const std::string& currency, const std::string& date) 
{
    transactions.emplace_back(nextTransactionId++, categoryId, amountMinorUnits, name, type, currency, date);
    data_version++;
}

void ExpenseManager::removeTransaction(unsigned int id) 
{
    transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
        [id](const Transaction& t) { return t.getId() == id; }),
        transactions.end());
    data_version++;
}

void ExpenseManager::addCategory(const std::string& name) 
{
    categories.emplace_back(nextCategoryId++, name);
    data_version++;
}

void ExpenseManager::removeCategory(unsigned int id) 
{
    transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
        [id](const Transaction& t) { return t.getCategoryId() == id; }),
        transactions.end());
    categories.erase(std::remove_if(categories.begin(), categories.end(),
        [id](const Category& c) { return c.getId() == id; }),
        categories.end());
    data_version++;
}

const std::vector<Transaction>& ExpenseManager::getTransactions() const
{
    return transactions;
}

const std::vector<Transaction> ExpenseManager::getFilteredTransactions(const Filter& filter) const
{
    std::vector<Transaction> filteredTransactions;
    std::copy_if(transactions.begin(), transactions.end(), std::back_inserter(filteredTransactions),
        [&filter](const Transaction& t) {
            bool matchesCategory = filter.categoryId == 0 ||
                t.getCategoryId() == filter.categoryId;

            bool matchesType = filter.type == TransactionTypeFilter::ALL ||
                (filter.type == TransactionTypeFilter::INCOME &&
                t.getType() == TransactionType::INCOME) ||
                (filter.type == TransactionTypeFilter::EXPENSE &&
                t.getType() == TransactionType::EXPENSE);

            bool matchesName = filter.name.empty() ||
                t.getName().find(filter.name) != std::string::npos;

            double amount = t.getAmountMinorUnits() / 100.0;

            bool matchesAmount =
                (filter.minAmount <= 0 || amount >= filter.minAmount) &&
                (filter.maxAmount <= 0 || amount <= filter.maxAmount);

            return matchesCategory && matchesType && matchesName && matchesAmount;
        });
    return filteredTransactions;
}

const std::vector<Category>& ExpenseManager::getCategories() const
{
    return categories;
}

const Category* ExpenseManager::getCategoryById(unsigned int id) const
{
    auto it = std::find_if(categories.begin(), categories.end(),
        [id](const Category& c) { return c.getId() == id; });
    return (it != categories.end()) ? &(*it) : nullptr;
}

bool ExpenseManager::saveToFile(const std::string& path) const
{
    nlohmann::json j;
    j["categories"] = nlohmann::json::array();
    j["transactions"] = nlohmann::json::array();

    for (const auto& category : categories)
    {
        j["categories"].push_back({
            {"id", category.getId()},
            {"name", category.getName()}
        });
    }

    for (const auto& transaction : transactions)
    {
        j["transactions"].push_back({
            {"id", transaction.getId()},
            {"categoryId", transaction.getCategoryId()},
            {"amountMinorUnits", transaction.getAmountMinorUnits()},
            {"name", transaction.getName()},
            {"type", transaction.getType() == TransactionType::INCOME ? "income" : "expense"},
            {"currency", transaction.getCurrency()},
            {"date", transaction.getDate()}
        });
    }

    std::ofstream file(path);

    if (!file.is_open())
        return false;

    file << j.dump(4);
    return file.good();

}

bool ExpenseManager::loadFromFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
        return false;

    try
    {
        nlohmann::json j;
        file >> j;

        std::vector<Category> loadedCategories;
        std::vector<Transaction> loadedTransactions;

        for (const auto& item : j.at("categories"))
        {
            loadedCategories.emplace_back(
                item.at("id").get<unsigned int>(),
                item.at("name").get<std::string>()
            );
        }

        for (const auto& item : j.at("transactions"))
        {
            TransactionType type =
                item.at("type").get<std::string>() == "income"
                    ? TransactionType::INCOME
                    : TransactionType::EXPENSE;

            loadedTransactions.emplace_back(
                item.at("id").get<unsigned int>(),
                item.at("categoryId").get<unsigned int>(),
                item.at("amountMinorUnits").get<std::int64_t>(),
                item.at("name").get<std::string>(),
                type,
                item.at("currency").get<std::string>(),
                item.at("date").get<std::string>()
            );
        }

        categories = std::move(loadedCategories);
        transactions = std::move(loadedTransactions);

        data_version++;

        nextCategoryId = 1;
        for (const auto& category : categories)
            nextCategoryId = std::max(nextCategoryId, category.getId() + 1);

        nextTransactionId = 1;
        for (const auto& transaction : transactions)
            nextTransactionId = std::max(nextTransactionId, transaction.getId() + 1);

        return true;
    }
    catch (const nlohmann::json::exception&)
    {
        return false;
    }
}

bool ExpenseManager::updateTransaction(
    unsigned int id,
    unsigned int categoryId,
    std::int64_t amountMinorUnits,
    const std::string& name,
    TransactionType type,
    const std::string& currency,
    const std::string& date)
{
    for (auto& transaction : transactions)
    {
        if (transaction.getId() == id)
        {
            transaction.update(categoryId, amountMinorUnits, name, type, currency, date);
            ++data_version;
            return true;
        }
    }

    return false;
}