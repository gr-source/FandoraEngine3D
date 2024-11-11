#include "Scene.h"

#include "../../Resources.h"
#include "../../GameObject.h"
#include "../../component/Transform.h"
#include "../../component/MeshRender.h"
#include "../../component/SunComponent.h"

Scenes::Scenes() : name("none") {}

Scenes::Scenes(const std::string& name) : name(name){}

void Scenes::add(const std::string& path) {
    GameObject *gameObject = nullptr;
    
    try {
    	gameObject = &Resources::Load<GameObject>(path);
    } catch (const std::exception &e) {
    	std::cout << "Scene.add " << e.what() << std::endl;
    }
    if (!gameObject)
	return;

     m_gameObjects.push_back(gameObject);

     gameObject->Instantiate();
}

void Scenes::addAll(const std::string& path) {
    auto objects = Resources::LoadAll<GameObject>(path);

    for (auto& gameObject : objects) {
        m_gameObjects.push_back(gameObject.get());

       // gameObjectList.push_back(std::move(gameObject));
    }
    gameObjectList.insert(gameObjectList.end(),
                              std::make_move_iterator(objects.begin()),
                              std::make_move_iterator(objects.end()));

}

void Scenes::remove(const GameObject* gameObject) {
    m_gameObjects.erase(std::remove_if(m_gameObjects.begin(), m_gameObjects.end(), [&gameObject](const GameObject* obj) {
        return gameObject == obj;
    }), m_gameObjects.end());

    gameObjectList.erase(std::remove_if(gameObjectList.begin(), gameObjectList.end(), [&gameObject](std::unique_ptr<GameObject>& obj) {
        if (gameObject == obj.get()) {
            MeshRender& meshrender = obj->GetComponent<MeshRender>();

            gameStatics.vertices -= meshrender.vertices;
            return true;
        }
        return false;
    }), gameObjectList.end());
}

