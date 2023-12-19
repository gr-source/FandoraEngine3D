#include "GameObject.h"
#include "ObjLoader.h"

#include "component/Transform.h"

Manager manager;

std::vector<std::unique_ptr<GameObject>> gameObjectList;

GameObject::GameObject() : name("none"), type(PrimitiveType::None), entity(&manager.CreateEntity()) {
}

GameObject::GameObject(const GameObject& other) : name(other.name), type(other.type), entity(&manager.CreateEntity()) {
    
}

GameObject::GameObject(const std::string& name) : name(name), type(PrimitiveType::None), entity(&manager.CreateEntity()) {
}

void GameObject::Instantiate() {
    std::unique_ptr<GameObject> ptr{this};

    gameObjectList.push_back(std::move(ptr));
}

void GameObject::Destroy() {
    auto it = std::remove_if(gameObjectList.begin(), gameObjectList.end(), [this](const std::unique_ptr<GameObject>& gameObject) {
        return this == gameObject.get();
    });

    if (it != gameObjectList.end()) {
        manager.Destroy(entity);
        gameObjectList.erase(it, gameObjectList.end());
    }
}

GameObject::~GameObject() {
    manager.Destroy(entity);

    std::cout << "[ Gameobject ] " << name << " " << gameObjectList.size() << std::endl;
}

GameObject& GameObject::CreatePrimitive(PrimitiveType type) {

    GameObject* gameObject = new GameObject();

    switch (type)
    {
    case PrimitiveType::Sphere:
        gameObject->name = "Sphere";
        break;
    case PrimitiveType::Cylinder:
        gameObject->name = "Cylinder";
        break;
    case PrimitiveType::Plane:
        gameObject->name = "Plane";
        break;
    case PrimitiveType::Cube:
        gameObject->name = "Cube";
        break;
    
    default:
        break;
    }


    gameObject->type = type;

    gameObject->AddComponent<Transform>();

    std::unique_ptr<GameObject> Ptr{gameObject};

    gameObjectList.push_back(std::move(Ptr));

    return *gameObject;
}





