#include "views/FilterView.hpp"
#include <imgui.h>
#include <cstring>

FilterView::FilterView(ExpenseManager& manager, Filter& filter)
    : manager(manager), filter(filter)
{
}

void FilterView::render()
{
    if (!ImGui::BeginPopupModal("Filter Transactions", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    const char* types[] = { "All", "Income", "Expense" };
    int selectedType = static_cast<int>(filter.type);

    if (ImGui::Combo("Type", &selectedType, types, IM_ARRAYSIZE(types)))
        filter.type = static_cast<TransactionTypeFilter>(selectedType);

    const auto& categories = manager.getCategories();
    std::vector<const char*> categoryNames;
    categoryNames.push_back("All");

    for (const auto& category : categories)
        categoryNames.push_back(category.getName().c_str());

    int selectedCategory = 0;

    for (int i = 0; i < static_cast<int>(categories.size()); i++)
    {
        if (categories[i].getId() == filter.categoryId)
        {
            selectedCategory = i + 1;
            break;
        }
    }

    if (ImGui::Combo("Category", &selectedCategory, categoryNames.data(),
                     static_cast<int>(categoryNames.size())))
    {
        filter.categoryId = selectedCategory == 0
            ? 0
            : categories[selectedCategory - 1].getId();
    }

    char nameBuffer[256]{};
    std::strncpy(nameBuffer, filter.name.c_str(), sizeof(nameBuffer) - 1);

    if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer)))
        filter.name = nameBuffer;

    ImGui::InputDouble("Amount from", &filter.minAmount, 0.0, 0.0, "%.2f");
    ImGui::InputDouble("Amount to", &filter.maxAmount, 0.0, 0.0, "%.2f");

    if (ImGui::Button("Close"))
        ImGui::CloseCurrentPopup();

    ImGui::EndPopup();
}