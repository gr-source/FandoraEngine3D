#include "window/Window.h"

int main() {
    std::unique_ptr<Window> scene = std::make_unique<Window>("Game Render", 1080, 600);
    while (scene->IsCloseWindow()) {
        scene->Update();
    }
    return EXIT_SUCCESS;
}



