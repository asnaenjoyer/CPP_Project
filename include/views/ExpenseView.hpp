#pragma once
#include "ExpenseManager.hpp"
#include "TransactionListView.hpp"
#include "AddTransactionView.hpp"
#include "CategoryView.hpp"
#include "FilterView.hpp"
#include "models/Filter.hpp"

class ExpenseView
{
private:
    ExpenseManager& expenseManager;

    int cachedDataVersion = -1;
    std::vector<Transaction> transactions;
    TransactionListView transactionListView;

    AddTransactionView addTransactionView;

    CategoryView categoryView;

    Filter filter = Filter();
    FilterView filterView;

    bool windowOpen = true;

public:
    explicit ExpenseView(ExpenseManager& manager);
    void render();
    bool isOpen() const { return windowOpen; }
};