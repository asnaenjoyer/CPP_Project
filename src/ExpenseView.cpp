#include "ExpenseView.hpp"

#include <imgui.h>

ExpenseView::ExpenseView(ExpenseManager& manager) : manager(manager) {}

void ExpenseView::render()
{
    ImGui::Begin("Expense Tracker");

    ImGui::Text("Dashboard");
    ImGui::Separator();

    if (ImGui::Button("+ Add Transaction"))
    {
        ImGui::OpenPopup("Add Transaction");
    }
    renderAddTransaction();

    ImGui::Spacing();

    const auto& transactions = manager.getTransactions();

    if (ImGui::BeginTable("Transactions", 4,
        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable))
    {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Category ID");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableSetupColumn("Date");
        ImGui::TableHeadersRow();

        for (const auto& transaction : transactions)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted(transaction.getName().c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%u", transaction.getCategoryId());

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
    if (ImGui::BeginPopupModal("Add Transaction", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("New transaction");

        if (ImGui::Button("Cancel"))
            ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }
}