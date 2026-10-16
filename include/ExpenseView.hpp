#pragma once

#include "ExpenseManager.hpp"

class ExpenseView
{
private:
    ExpenseManager& manager;

    bool showAddTransaction = false;

    void renderAddTransaction();
    

public:
    explicit ExpenseView(ExpenseManager& manager);
    void render();
};