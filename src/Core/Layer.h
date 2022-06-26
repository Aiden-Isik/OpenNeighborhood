#pragma once

#include "Events/Event.h"

class Layer
{
public:
    Layer(const std::string &) {}

    virtual ~Layer() {}

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate() {}

    virtual void OnEvent(Event &) {}
};
