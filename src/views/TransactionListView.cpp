#include "views/TransactionListView.hpp"

#include <imgui.h>

#include <vector>

TransactionListView::TransactionListView(ExpenseManager& manager)
    : manager(manager) {}

void TransactionListView::render()
{
    const auto& transactions = manager.getTransactions();

    if (ImGui::BeginTable("Transactions", 5,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable))
    {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Category");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableSetupColumn("Date");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();

        std::vector<unsigned int> transactionsToDelete;

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

            ImGui::TableSetColumnIndex(4);
            ImGui::PushID(transaction.getId());

            if (ImGui::Button("Delete"))
                transactionsToDelete.push_back(transaction.getId());

            ImGui::PopID();
        }

        ImGui::EndTable();

        for (unsigned int id : transactionsToDelete)
            manager.removeTransaction(id);
    }
}