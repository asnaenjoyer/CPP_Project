#include "ExpenseManager.hpp"
#include <algorithm>
#include <iterator>

unsigned int ExpenseManager::nextTransactionId = 1;
unsigned int ExpenseManager::nextCategoryId = 1;

void ExpenseManager::addTransaction(unsigned int categoryId, std::int64_t amountMinorUnits,
                                    const std::string& name, TransactionType type,
                                    const std::string& currency, const std::string& date) 
{
    transactions.emplace_back(nextTransactionId++, categoryId, amountMinorUnits, name, type, currency, date);
}

void ExpenseManager::removeTransaction(unsigned int id) 
{
    transactions.erase(std::remove_if(transactions.begin(), transactions.end(),
        [id](const Transaction& t) { return t.getId() == id; }),
        transactions.end());
}

void ExpenseManager::addCategory(const std::string& name) 
{
    categories.emplace_back(nextCategoryId++, name);
}

void ExpenseManager::removeCategory(unsigned int id) 
{
    categories.erase(std::remove_if(categories.begin(), categories.end(),
        [id](const Category& c) { return c.getId() == id; }),
        categories.end());
}

const std::vector<Transaction>& ExpenseManager::getTransactions() const
{
    return transactions;
}

std::vector<Transaction> ExpenseManager::getTransactions(unsigned int categoryId) const
{
    std::vector<Transaction> filteredTransactions;
    std::copy_if(transactions.begin(), transactions.end(), std::back_inserter(filteredTransactions),
        [categoryId](const Transaction& t) { return t.getCategoryId() == categoryId; });
    return filteredTransactions;
}

const std::vector<Category>& ExpenseManager::getCategories() const
{
    return categories;
}