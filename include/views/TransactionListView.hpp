#pragma once
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

    void renderAddTransaction();

public:
    explicit TransactionListView(ExpenseManager& manager);
    void render();
};