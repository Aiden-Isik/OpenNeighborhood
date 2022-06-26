#pragma once

#include "Render/ImGuiCustomWidgets.h"
#include "Events/AppEvent.h"

class Panel
{
public:
    Panel();
    virtual ~Panel() = default;

    virtual void OnRender() = 0;
    virtual void OnEvent(Event &event);

protected:
    float m_Margin = 20.0f;
    float m_WindowWidth;
    float m_WindowHeight;

private:
    bool OnWindowResize(WindowResizeEvent &event);
    void SetWindowWidthAndHeight();
};
