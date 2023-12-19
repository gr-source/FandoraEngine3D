#pragma once

#include "../engine/Global.h"
#include "../engine/Shader.h"
#include "../engine/Camera.h"

class Game {
private:
public:
    Game() = default;
    ~Game();
    
    void Start();
    void Update();
    void Render();
    void Gui();
};




