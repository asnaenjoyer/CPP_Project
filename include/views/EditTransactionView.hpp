#pragma once

#include "ExpenseManager.hpp"

class EditTransactionView
{
private:
    ExpenseManager& manager;

    unsigned int transactionId = 0;
    unsigned int selectedCategoryId = 0;

    char nameBuffer[256]{};
    char dateBuffer[32]{};
    char currencyBuffer[16]{};

    double amount = 0.0;
    TransactionType selectedType = TransactionType::EXPENSE;

    bool open = false;

public:
    EditTransactionView(ExpenseManager& manager);

    void setTransactionId(unsigned int id);
    void openView();
    void render();
};