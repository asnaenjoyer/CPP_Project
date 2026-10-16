#include "views/CategoryView.hpp"

#include <imgui.h>

CategoryView::CategoryView(ExpenseManager& manager)
    : manager(manager) {}

void CategoryView::render()
{
    if (!ImGui::BeginPopupModal("Manage Categories", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        return;

    ImGui::Text("Categories");
    ImGui::Separator();

    ImGui::InputText("##CategoryName", categoryName, sizeof(categoryName));
    ImGui::SameLine();

    if (ImGui::Button("Add") && categoryName[0] != '\0')
    {
        manager.addCategory(categoryName);
        categoryName[0] = '\0';
    }

    ImGui::Separator();

    for (const auto& category : manager.getCategories())
    {
        ImGui::PushID(category.getId());
        ImGui::TextUnformatted(category.getName().c_str());
        ImGui::SameLine();

        if (ImGui::Button("Delete"))
        {
            categoryToDelete = category.getId();
            ImGui::OpenPopup("Confirm Delete");
        }

        ImGui::PopID();
    }

    if (ImGui::Button("Close"))
        ImGui::CloseCurrentPopup();

    if (ImGui::BeginPopupModal("Confirm Delete", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Delete this category?");

        if (ImGui::Button("Yes"))
        {
            manager.removeCategory(categoryToDelete);
            categoryToDelete = 0;
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button("No"))
        {
            categoryToDelete = 0;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::EndPopup();
}