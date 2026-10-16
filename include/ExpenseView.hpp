#pragma once

#include "ExpenseManager.hpp"

class ExpenseView
{
private:
    ExpenseManager& manager;

    bool showAddTransaction = false;

    void renderAddTransaction();

    char transactionName[128] = "";
    char amount[32] = "";
    char date[16] = "2026-10-16";
    char currency[8] = "UAH";
    int transactionType = 1;
    int selectedCategory = 0;

    void renderAddCategory();
    char categoryName[128] = "";

    bool windowOpen = true;
    
public:
    explicit ExpenseView(ExpenseManager& manager);
    void render();
    bool isOpen() const { return windowOpen; }
};