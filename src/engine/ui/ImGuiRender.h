#pragma once

#include "../Global.h"

class ImGuiRender {
public:

    ImGuiRender() = default;

    ImGuiRender(const char* openglVersion);

    void Begin();

    void End();

    ~ImGuiRender();
private:
};


