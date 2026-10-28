#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include "models/Transaction.hpp"
#include "models/Category.hpp"
#include "models/Filter.hpp"

class ExpenseManager 
{
    private:
        std::vector<Transaction> transactions;
        std::vector<Category> categories;

        static unsigned int nextTransactionId;
        static unsigned int nextCategoryId;

        int data_version = 0;

    public:
        void addTransaction(unsigned int categoryId, std::int64_t amountMinorUnits,
                            const std::string& name, TransactionType type,
                            const std::string& currency, const std::string& date);
        void removeTransaction(unsigned int id);

        void addCategory(const std::string& name);
        void removeCategory(unsigned int id);

        const std::vector<Transaction>& getTransactions() const;

        const std::vector<Transaction> getFilteredTransactions(const Filter& filter) const;

        const std::vector<Category>& getCategories() const;

        const Category* getCategoryById(unsigned int id) const;

        bool saveToFile(const std::string& path) const;
        bool loadFromFile(const std::string& path);

        int getDataVersion() const { return data_version; }
};