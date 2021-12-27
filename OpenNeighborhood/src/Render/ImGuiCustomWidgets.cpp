#include "pch.h"
#include "Render/ImGuiCustomWidgets.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <ImGui/imgui_internal.h>


namespace ImGui
{
    bool ImageButtonWithText(ImTextureID userTextureID, const ImVec2 &imageSize, const ImVec2 &totalSize, const char *label, const ImVec2 &padding)
    {
        ImGuiWindow *window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        const ImGuiID id = window->GetID(label);

        const ImRect totalRect(window->DC.CursorPos, window->DC.CursorPos + totalSize + padding * 2);
        const ImRect imageRect(window->DC.CursorPos + padding, window->DC.CursorPos + imageSize + padding);

        ItemSize(totalRect);
        if (!ItemAdd(totalRect, id))
            return false;

        bool hovered, held;
        int flags = ImGuiButtonFlags_PressedOnClick |
            ImGuiButtonFlags_PressedOnDoubleClick |
            ImGuiButtonFlags_MouseButtonLeft |
            ImGuiButtonFlags_MouseButtonRight;

        bool pressed = ButtonBehavior(totalRect, id, &hovered, &held, flags);

        const ImU32 color = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        RenderFrame(totalRect.Min, totalRect.Max, color, true, ImClamp((float)ImMin(padding.x, padding.y), 0.0f, 0.0f));
        window->DrawList->AddImage(userTextureID, imageRect.Min, imageRect.Max, ImVec2(0.0f, 0.0f), ImVec2(1.0f, 1.0f), GetColorU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)));

        ImRect offset = totalRect;
        offset.Min.x = imageRect.Max.x + padding.x;
        RenderTextWrapped(offset.Min + padding * 2.0f, label, NULL, totalSize.x - imageSize.x - padding.x * 2.0f);

        return pressed;
    }
}
