#include "views/TransactionListView.hpp"

#include <imgui.h>
#include <iostream>
#include <vector>
#include <algorithm>

TransactionListView::TransactionListView(ExpenseManager& manager)
    : manager(manager) {}

void TransactionListView::render()
{
    if (ImGui::BeginTable("Transactions", 5,
        ImGuiTableFlags_Borders |
        ImGuiTableFlags_RowBg |
        ImGuiTableFlags_Resizable |
        ImGuiTableFlags_Sortable))
    {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Category");
        ImGui::TableSetupColumn("Amount");
        ImGui::TableSetupColumn("Date");
        ImGui::TableSetupColumn("Actions");
        ImGui::TableHeadersRow();

        sortSpecs = ImGui::TableGetSortSpecs();

        bool dataChanged = cachedDataVersion != manager.getDataVersion();

        if (dataChanged)
        {
            transactions = manager.getTransactions();
            cachedDataVersion = manager.getDataVersion();
        }

        if (sortSpecs && (dataChanged || sortSpecs->SpecsDirty))
        {
            transactions = sortTransactions(transactions, sortSpecs);
            sortSpecs->SpecsDirty = false;
        }

        std::vector<unsigned int> transactionsToDelete;

        double total = 0.0;

        for (const auto& transaction : transactions)
        {
            double amount = transaction.getAmountMinorUnits() / 100.0;

            if (transaction.getType() == TransactionType::INCOME)
                total += amount;
            else
                total -= amount;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TextUnformatted(transaction.getName().c_str());

            ImGui::TableSetColumnIndex(1);
            const auto* category = manager.getCategoryById(transaction.getCategoryId());
            ImGui::TextUnformatted(category ? category->getName().c_str() : "Unknown");

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%s%.2f %s",
                transaction.getType() == TransactionType::INCOME ? "+" : "-",
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

        ImGui::TableNextRow(ImGuiTableRowFlags_None);

        ImGui::TableSetColumnIndex(0);
        ImGui::TextUnformatted("TOTAL");

        ImGui::TableSetColumnIndex(2);
        ImGui::Text("%s%.2f UAH", total < 0 ? "-" : "+", std::abs(total));

        ImGui::EndTable();

        for (unsigned int id : transactionsToDelete)
            manager.removeTransaction(id);

        if (!transactionsToDelete.empty())
            manager.saveToFile("data/data.json");
    }
}

std::vector<Transaction> TransactionListView::sortTransactions(std::vector<Transaction> transactions, ImGuiTableSortSpecs* sortSpecs)
{
    if (!sortSpecs || sortSpecs->SpecsCount == 0)
        return transactions;

    const ImGuiTableColumnSortSpecs* sortSpec = &sortSpecs->Specs[0];

    std::sort(transactions.begin(), transactions.end(),
        [this, sortSpec](const Transaction& a, const Transaction& b) {
            int result = 0;
            switch (sortSpec->ColumnIndex)
            {
            case 0: // Name
                result = a.getName().compare(b.getName());
                break;
            case 1: // Category
                result = a.getCategoryId() - b.getCategoryId();
                break;
            case 2: // Amount
            {
                double amountA = convertToMajorUnits(a.getAmountMinorUnits(), a.getType());
                double amountB = convertToMajorUnits(b.getAmountMinorUnits(), b.getType());
                result = amountA < amountB ? -1 : amountA > amountB ? 1 : 0;
                break;
            }
            case 3: // Date
                result = a.getDate().compare(b.getDate());
                break;
            default:
                break;
            }
            return sortSpec->SortDirection == ImGuiSortDirection_Ascending ? result < 0 : result > 0;
        });

    return transactions;
}

double TransactionListView::convertToMajorUnits(std::int64_t amountMinorUnits, TransactionType type)
{
    double majorUnits = amountMinorUnits / 100.0;
    return type == TransactionType::INCOME ? majorUnits : -majorUnits;
}