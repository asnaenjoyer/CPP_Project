#pragma once

#include <vector>
#include <string>
#include <cstdint>

#include "models/Transaction.hpp"
#include "models/Category.hpp"

class ExpenseManager 
{
    private:
        std::vector<Transaction> transactions;
        std::vector<Category> categories;

        static unsigned int nextTransactionId;
        static unsigned int nextCategoryId;

    public:
        void addTransaction(unsigned int categoryId, std::int64_t amountMinorUnits,
                            const std::string& name, TransactionType type,
                            const std::string& currency, const std::string& date);
        void removeTransaction(unsigned int id);

        void addCategory(const std::string& name);
        void removeCategory(unsigned int id);

        const std::vector<Transaction>& getTransactions() const;
        std::vector<Transaction> getTransactions(unsigned int categoryId) const;

        const std::vector<Category>& getCategories() const;

};