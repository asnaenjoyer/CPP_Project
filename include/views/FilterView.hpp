#pragma once
#include "models/Filter.hpp"
#include "ExpenseManager.hpp"

class FilterView
{    
private:
    Filter& filter;
    ExpenseManager& manager;

public:
    explicit FilterView(ExpenseManager& manager, Filter& filter);
    void render();
};
