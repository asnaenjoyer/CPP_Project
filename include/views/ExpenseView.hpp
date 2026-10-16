#pragma once
#include "ExpenseManager.hpp"
#include "TransactionListView.hpp"
#include "AddTransactionView.hpp"
#include "CategoryView.hpp"

class ExpenseView
{
private:
    TransactionListView transactionListView;
    AddTransactionView addTransactionView;
    CategoryView categoryView;

    bool windowOpen = true;

public:
    explicit ExpenseView(ExpenseManager& manager);
    void render();
    bool isOpen() const { return windowOpen; }
};