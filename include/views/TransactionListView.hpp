#pragma once
#include <imgui.h>

#include "ExpenseManager.hpp"

class TransactionListView
{
private:
    ExpenseManager& manager;

    ImGuiTableSortSpecs* sortSpecs;
    std::vector<Transaction> sortTransactions(std::vector<Transaction> transactions, ImGuiTableSortSpecs* sortSpecs);
    double convertToMajorUnits(std::int64_t amountMinorUnits, TransactionType type);

public:
    explicit TransactionListView(ExpenseManager& manager);
    void render(const std::vector<Transaction>& transactions);
};