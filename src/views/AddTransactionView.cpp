#include "views/AddTransactionView.hpp"

#include <imgui.h>

#include <cmath>
#include <cstdlib>
#include <cstdint>

AddTransactionView::AddTransactionView(ExpenseManager& manager)
    : manager(manager) {}

void AddTransactionView::render()
{
    if (!ImGui::BeginPopupModal("Add Transaction", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    ImGui::Text("New transaction");
    ImGui::Separator();

    ImGui::InputText("Name", transactionName, sizeof(transactionName));
    ImGui::InputText("Amount", amount, sizeof(amount));

    const char* types[] = { "Income", "Expense" };
    ImGui::Combo("Type", &transactionType, types, IM_ARRAYSIZE(types));

    const auto& categories = manager.getCategories();

    if (categories.empty())
    {
        ImGui::Text("Add a category first.");
    }
    else
    {
        if (selectedCategory >= static_cast<int>(categories.size()))
            selectedCategory = 0;

        if (ImGui::BeginCombo("Category", categories[selectedCategory].getName().c_str()))
        {
            for (int i = 0; i < static_cast<int>(categories.size()); ++i)
            {
                bool selected = selectedCategory == i;

                if (ImGui::Selectable(categories[i].getName().c_str(), selected))
                    selectedCategory = i;

                if (selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
    }

    ImGui::InputText("Currency", currency, sizeof(currency));
    ImGui::InputText("Date (YYYY-MM-DD)", date, sizeof(date));

    ImGui::Spacing();
    ImGui::Separator();

    if (ImGui::Button("Save") && !categories.empty())
    {
        double value = std::strtod(amount, nullptr);
        auto amountMinorUnits = static_cast<std::int64_t>(std::llround(value * 100));

        manager.addTransaction(
            categories[selectedCategory].getId(),
            amountMinorUnits,
            transactionName,
            transactionType == 0 ? TransactionType::INCOME : TransactionType::EXPENSE,
            currency,
            date
        );
        manager.saveToFile("data/data.json");
        transactionName[0] = '\0';
        amount[0] = '\0';

        ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}