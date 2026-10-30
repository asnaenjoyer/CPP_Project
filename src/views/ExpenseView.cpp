#include "views/ExpenseView.hpp"

#include <imgui.h>

ExpenseView::ExpenseView(ExpenseManager& manager)
    : expenseManager(manager),
    editTransactionView(manager),
      transactionListView(manager, editTransactionView),
      addTransactionView(manager),
      categoryView(manager),
      filterView(manager, filter)
      {}

void ExpenseView::render()
{
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);

    ImGui::Begin("Expense Tracker", &windowOpen,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse);

    ImGui::Separator();

    if (ImGui::Button("+ Add Transaction"))
        ImGui::OpenPopup("Add Transaction");

    ImGui::SameLine();

    if (ImGui::Button("Manage Categories"))
        ImGui::OpenPopup("Manage Categories");

    ImGui::SameLine();

    if (ImGui::Button("Filter"))
        ImGui::OpenPopup("Filter Transactions");

    addTransactionView.render();
    categoryView.render();
    filterView.render();
    editTransactionView.render();

    ImGui::Spacing();

    transactionListView.render(expenseManager.getFilteredTransactions(filter));

    ImGui::End();
}