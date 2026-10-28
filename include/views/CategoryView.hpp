#pragma once

#include "ExpenseManager.hpp"

class CategoryView
{
private:
    ExpenseManager& manager;

    char categoryName[128] = "";
    unsigned int categoryToDelete = 0;

    bool openDeletePopup = false;

public:
    explicit CategoryView(ExpenseManager& manager);
    void render();
};