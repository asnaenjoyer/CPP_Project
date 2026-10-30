#pragma once
#include "ExpenseManager.hpp"
#include "TransactionListView.hpp"
#include "EditTransactionView.hpp"
#include "AddTransactionView.hpp"
#include "CategoryView.hpp"
#include "FilterView.hpp"
#include "models/Filter.hpp"

class ExpenseView
{
private:
    ExpenseManager& expenseManager;
    Filter filter = Filter();

    TransactionListView transactionListView;
    AddTransactionView addTransactionView;
    EditTransactionView editTransactionView;
    CategoryView categoryView;
    FilterView filterView;

    bool windowOpen = true;

public:
    explicit ExpenseView(ExpenseManager& manager);
    void render();
    bool isOpen() const { return windowOpen; }
};