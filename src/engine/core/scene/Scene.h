#pragma once

#include "../../Global.h"

class Scenes {
private:
public:
    std::vector<GameObject*> m_gameObjects;
    std::string name;
    
    Scenes();
    Scenes(const std::string& name);

    void add(const std::string& path);
    void addAll(const std::string& path);

    void remove(const GameObject* gameObject);
};


