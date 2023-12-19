#include "Template.h"

#include "../../Global.h"
#include "../../Screen.h"

void Template::AlertWindow(const char* title, const char* message, const AlertType& type) {
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::CalcTextSize(message).y * 5), ImGuiCond_Appearing);
    ImGui::SetNextWindowPos(ImVec2(Screen::width - 300, Screen::height - 200), ImGuiCond_Appearing);
    ImGui::Begin("{AlertWindown}", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    ImGui::SetCursorPosX((ImGui::GetWindowWidth() / 2) - ImGui::CalcTextSize(title).x);
    ImGui::TextColored(ImColor(255, 255, 255), "%s", title);

    ImColor clr;
    if (type == AlertType::ERROR) clr = {255, 50, 50, 255};
    else if (type == AlertType::SUCCESS) clr = {50, 255, 50, 255};
    else if (type == AlertType::NONE) clr = {150, 150, 150, 150};

    ImGui::TextColored(clr, "%s", message);
    ImGui::End();
}