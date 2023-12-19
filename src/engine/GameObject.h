#pragma once

#include "Global.h"

class GameObject {
private:
    Entity* entity;
public:
    PrimitiveType type;
    std::string name;
    std::string path;

    GameObject();

    GameObject(const GameObject& gameObject);

    GameObject(const std::string& name);

    template <typename T, typename ...Argv>
    T& AddComponent(Argv&&... argv) const {
        return entity->AddComponent<T>(std::forward<Argv>(argv)...);
    }

    template <typename T>
    T& GetComponent() const {
        return entity->GetComponent<T>();
    }

    void Instantiate();

    void Destroy();

    GameObject& Clone();

    ~GameObject();
    
    static GameObject& CreatePrimitive(PrimitiveType type);

};

