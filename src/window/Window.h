#pragma once

#include "../engine/Global.h"

class Window {
private:
    GLFWwindow* window;
    std::unique_ptr<Game> game;
    std::unique_ptr<ImGuiRender> imGuiRender;
public:
    Window() = default;

    Window(const char* title, int screenWidth, int screenHeight);

    void Start();

    void Update();

    bool IsCloseWindow() const;

    ~Window();
};



