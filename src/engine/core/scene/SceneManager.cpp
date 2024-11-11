#include "SceneManager.h"
#include "Scene.h"

#include "../../GameObject.h"

#include "../../component/Transform.h"

SceneManager::SceneManager() {}

SceneManager::~SceneManager() {}

void SceneManager::createScenes(const std::string& name) {
    std::unique_ptr<Scenes> scenes = std::make_unique<Scenes>(name);
     scenes->add("Cube");

    m_scenes.push_back(std::move(scenes)); //mover o original pra lista
}

void SceneManager::loadFromFile(const std::string& path) {
    std::string pathToFile = Global::IsContains(path, "/") ? path : "src/assets/scenes/" + path + ".scn";

    std::fstream scn(pathToFile, std::ios::in);
    if (!scn.is_open()) {
        m_hasScenes = false;
        return;
    }

    std::unique_ptr<Scenes> scenes = std::make_unique<Scenes>();

    std::string line;
    while (std::getline(scn, line)) {
        std::stringstream ss(line);

        std::string key;
        if (!(ss >> key)) continue;

        if (Global::IsEquals(key, "name")) {
            if (!(ss >> scenes->name)) continue;
        } if (Global::IsEquals(key, "object")) {
            std::string name, path;
            Vector3 position;
            bool all;

            if (!(ss >> name >> path >> position >> all)) {
                continue;
            }
            scenes->add(path);
        }
    }
    m_scenes.push_back(std::move(scenes)); // mover o originale pra lista
    scn.close();

    m_hasScenes = true;
}

void SceneManager::loadAllScenes() {
    auto path = "src/assets/scenes";
    
    if (!std::filesystem::exists(path)) {
    	std::cout << "Scenes dir do not found: " << path << std::endl;    	
		return;
    }
	for (auto& it : std::filesystem::directory_iterator(path)) {
        if (it.path().extension() != std::filesystem::path(".scn")) continue;

        loadFromFile(it.path().string());
    }
}

void SceneManager::renamescene(const std::string& newName) {
    auto& scene = m_scenes.back();

    std::rename(std::string("src/assets/scenes/" + scene->name + ".scn").c_str(), std::string("src/assets/scenes/" + newName + ".scn").c_str());

    scene->name = newName;
}

void SceneManager::saveScenes() {
    std::string path = "src/assets/scenes/";
    
    if (!std::filesystem::exists(path)) {
    	std::cout << "Scenes dir do not found: " << path << std::endl;    	
		return;
    }
    
    const auto& scene = m_scenes.back();

    std::fstream file(path + scene->name + ".scn", std::ios::out);
    file << "name" << " " << scene->name << std::endl;

    for (const auto& gameObject : scene->m_gameObjects) {
        Transform& transform = gameObject->GetComponent<Transform>();

        file << "object" << " " << gameObject->name << " " << gameObject->path << " " << transform.position << std::endl;
    }
    file.close();
}

void SceneManager::saveAllScenes() {
	std::string path = "src/assets/scenes/";
    
    if (!std::filesystem::exists(path)) {
    	std::cout << "Scenes dir do not found: " << path << std::endl;    	
		return;
    }
    
    for (const auto& scene : m_scenes) {
        std::fstream file(path + scene->name + ".scn", std::ios::out);
        file << "name" << " " << scene->name << std::endl;

        for (const auto& gameObject : scene->m_gameObjects) {
            Transform& transform = gameObject->GetComponent<Transform>();

            file << "object" << " " << gameObject->name << " " << gameObject->path << " " << transform.position << std::endl;
        }
        file.close();
    }
}

bool SceneManager::hasScenes() const {
    return m_hasScenes;
}



