#pragma once
#include <string>

enum class TransactionTypeFilter
{
    ALL,
    INCOME,
    EXPENSE
};

struct Filter
{
    unsigned int categoryId = 0;
    TransactionTypeFilter type = TransactionTypeFilter::ALL;
    std::string name;
    double minAmount = 0.0;
    double maxAmount = 0.0;
};