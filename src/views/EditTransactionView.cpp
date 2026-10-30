#include "views/EditTransactionView.hpp"
#include <imgui.h>
#include <cstdio>
#include <cmath>

EditTransactionView::EditTransactionView(ExpenseManager& manager)
    : manager(manager)
{
}

void EditTransactionView::setTransactionId(unsigned int id)
{
    transactionId = id;

    for (const auto& transaction : manager.getTransactions())
    {
        if (transaction.getId() != id)
            continue;

        std::snprintf(nameBuffer, sizeof(nameBuffer), "%s",
            transaction.getName().c_str());

        std::snprintf(dateBuffer, sizeof(dateBuffer), "%s",
            transaction.getDate().c_str());

        std::snprintf(currencyBuffer, sizeof(currencyBuffer), "%s",
            transaction.getCurrency().c_str());

        amount = transaction.getAmountMinorUnits() / 100.0;
        selectedCategoryId = transaction.getCategoryId();
        selectedType = transaction.getType();

        break;
    }
}

void EditTransactionView::openView()
{
    open = true;
}

void EditTransactionView::render()
{
    if (open)
    {
        ImGui::OpenPopup("Edit Transaction");
        open = false;
    }

    if (!ImGui::BeginPopupModal("Edit Transaction", nullptr,
        ImGuiWindowFlags_AlwaysAutoResize))
        return;

    ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer));
    ImGui::InputDouble("Amount", &amount, 0.01, 1.0, "%.2f");
    ImGui::InputText("Date", dateBuffer, sizeof(dateBuffer));
    ImGui::InputText("Currency", currencyBuffer, sizeof(currencyBuffer));

    if (ImGui::BeginCombo("Type",
        selectedType == TransactionType::INCOME ? "Income" : "Expense"))
    {
        if (ImGui::Selectable("Income", selectedType == TransactionType::INCOME))
            selectedType = TransactionType::INCOME;

        if (ImGui::Selectable("Expense", selectedType == TransactionType::EXPENSE))
            selectedType = TransactionType::EXPENSE;

        ImGui::EndCombo();
    }

    const Category* selectedCategory = manager.getCategoryById(selectedCategoryId);

    if (ImGui::BeginCombo("Category",
        selectedCategory ? selectedCategory->getName().c_str() : "Unknown"))
    {
        for (const auto& category : manager.getCategories())
        {
            bool selected = selectedCategoryId == category.getId();

            if (ImGui::Selectable(category.getName().c_str(), selected))
                selectedCategoryId = category.getId();
        }

        ImGui::EndCombo();
    }

    ImGui::Separator();

    if (ImGui::Button("Save"))
    {
        if (amount > 0.0 && std::isfinite(amount))
        {
            auto minorUnits = static_cast<std::int64_t>(
                std::llround(amount * 100.0));

            bool updated = manager.updateTransaction(
                transactionId,
                selectedCategoryId,
                minorUnits,
                nameBuffer,
                selectedType,
                currencyBuffer,
                dateBuffer
            );

            if (updated)
            {
                manager.saveToFile("data/data.json");
                ImGui::CloseCurrentPopup();
            }
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}