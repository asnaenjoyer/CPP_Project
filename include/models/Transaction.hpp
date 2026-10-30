#pragma once
#include <string>
#include <cstdint>

enum class TransactionType
{
    INCOME,
    EXPENSE
};

class Transaction 
{
    private:
        unsigned int id;
        unsigned int categoryId;
        std::int64_t amountMinorUnits;
        std::string name;
        TransactionType type;
        std::string currency;
        std::string date; // Format: YYYY-MM-DD
        
    public:
        Transaction(unsigned int id, unsigned int categoryId, std::int64_t amountMinorUnits, const std::string& name, TransactionType type, const std::string& currency, const std::string& date)
            : id(id), categoryId(categoryId), amountMinorUnits(amountMinorUnits), name(name), type(type), currency(currency), date(date) {}

        unsigned int getId() const { return id; }
        unsigned int getCategoryId() const { return categoryId; }
        std::int64_t getAmountMinorUnits() const { return amountMinorUnits; }
        const std::string& getName() const { return name; }
        TransactionType getType() const { return type; }
        const std::string& getCurrency() const { return currency; }
        const std::string& getDate() const { return date; }
        void update(unsigned int categoryId, std::int64_t amountMinorUnits,
            const std::string& name, TransactionType type,
            const std::string& currency, const std::string& date)
        {
            this->categoryId = categoryId;
            this->amountMinorUnits = amountMinorUnits;
            this->name = name;
            this->type = type;
            this->currency = currency;
            this->date = date;
        }
};