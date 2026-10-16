#include "ExpenseView.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

#include <cmath>
#include <cstdlib>
#include <cstdint>

ExpenseView::ExpenseView(ExpenseManager& manager) : manager(manager) {}

void ExpenseView::render()
{
    ImGui::Begin("Expense Tracker", &windowOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);


    ImGui::Text("Dashboard");
    ImGui::Separator();

    if (ImGui::Button("+ Add Transaction"))
    {
        ImGui::OpenPopup("Add Transaction");
    }
    ImGui::SameLine();
    if (ImGui::Button("+ Add Category"))
    {
        ImGui::OpenPopup("Add Category");
    }

    renderAddTransaction();
    renderAddCategory();

    ImGui::Spacing();

    const auto& transactions = manager.getTransactions();

    if (ImGui::BeginTable("Transactions", 4,
        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
    {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Category");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableSetupColumn("Date");
        ImGui::TableHeadersRow();

        for (const auto& transaction : transactions)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted(transaction.getName().c_str());

            ImGui::TableSetColumnIndex(1);
            const auto* category = manager.getCategoryById(transaction.getCategoryId());
            ImGui::TextUnformatted(category ? category->getName().c_str() : "Unknown");

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%.2f %s",
                transaction.getAmountMinorUnits() / 100.0,
                transaction.getCurrency().c_str());

            ImGui::TableSetColumnIndex(3);
            ImGui::TextUnformatted(transaction.getDate().c_str());
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

void ExpenseView::renderAddTransaction()
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

        transactionName[0] = '\0';
        amount[0] = '\0';
        ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}

void ExpenseView::renderAddCategory()
{
    if (!ImGui::BeginPopupModal("Add Category", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    ImGui::Text("New category");
    ImGui::Separator();

    ImGui::InputText("Name", categoryName, sizeof(categoryName));

    ImGui::Spacing();
    ImGui::Separator();

    if (ImGui::Button("Save"))
    {
        manager.addCategory(categoryName);
        categoryName[0] = '\0';
        ImGui::CloseCurrentPopup();
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}