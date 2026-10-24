#pragma once
#include <imgui.h>

#include "../ExpenseManager.hpp"

class TransactionListView
{
private:
    ExpenseManager& manager;

    char transactionName[128] = "";
    char amount[32] = "";
    char date[16] = "2026-10-16";
    char currency[8] = "UAH";
    int transactionType = 1;
    int selectedCategory = 0;
    ImGuiTableSortSpecs* sortSpecs;

    std::vector<Transaction> transactions;
    int cachedDataVersion = -1;

    std::vector<Transaction> sortTransactions(std::vector<Transaction> transactions, ImGuiTableSortSpecs* sortSpecs);
    double convertToMajorUnits(std::int64_t amountMinorUnits, TransactionType type);

public:
    explicit TransactionListView(ExpenseManager& manager);
    void render();
};