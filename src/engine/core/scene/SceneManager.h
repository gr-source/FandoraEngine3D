#pragma once

#include "../../Global.h"

class SceneManager {
private:
    bool m_hasScenes;
public:
    std::vector<std::unique_ptr<Scenes>> m_scenes;
    
    SceneManager();
    ~SceneManager();

    void createScenes(const std::string& name);
    void loadFromFile(const std::string& name);
    void loadAllScenes();
    void renamescene(const std::string& newName);
    void saveScenes();
    void saveAllScenes();
    
    bool hasScenes() const;
};

