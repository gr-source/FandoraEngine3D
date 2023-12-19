#include "Engine.h"
#include "GameObject.h"

void Engine::load(GameObject* _gameObject, bool _enable) { 
    gameObject = _gameObject;
    enable = _enable;
}



