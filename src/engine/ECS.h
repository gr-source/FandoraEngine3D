#pragma once

#include <iostream>
#include <memory>
#include <array>
#include <vector>

struct GameStatics {
	std::size_t vertices;
	std::size_t entities;
};

extern GameStatics gameStatics;

class Entity;

class Component {
private:
public:
    Entity* entity;

    virtual void Start() {}

    virtual void Update() {}

    virtual void Render() {}

    virtual ~Component() {}

    virtual std::unique_ptr<Component> Clone() {
        return nullptr;
    }
};

using ComponentID = std::size_t;

inline ComponentID GetComponentID() noexcept {
    static ComponentID nextID = 0;
    return nextID++;
}

template <typename T>
inline ComponentID GetComponentID() noexcept {
    static ComponentID nextComponetID = GetComponentID();
    return nextComponetID;
}

class Entity {
private:
public:
    std::vector<std::unique_ptr<Component>> components;
    std::array<Component*, 32> componentArray;

    
    Entity() = default;

    template <typename T, typename ...Argv>
    T& AddComponent(Argv&&... argv) {
        T* t = new T(std::forward<Argv>(argv)...);

        std::unique_ptr<T> Ptr{t};

        components.push_back(std::move(Ptr));
        componentArray[GetComponentID<T>()] = t;
        
        t->entity = this;
        t->Start();

        return *t;
    }

    template <typename T>
    T& GetComponent() {
        return *reinterpret_cast<T*>(componentArray[GetComponentID<T>()]);
    }

    void Update() {
        for (auto& c : components) c->Update();
    }

    void Render() {
        for (auto& c : components) c->Render();
    }

    void Clear() {
        components.clear();
        for (std::size_t i{};i<componentArray.size();++i) {
            componentArray[i] = nullptr;
        }
    }
};

class Manager {
private:
public:
    std::vector<std::unique_ptr<Entity>> entityList;
    
    Entity& CreateEntity() {
        gameStatics.entities++;

        entityList.push_back(std::move(std::make_unique<Entity>()));
        return *entityList.back();
    }

    void Destroy(Entity* other) {
        entityList.erase(std::remove_if(entityList.begin(), entityList.end(), [&other](auto& entity) {
            if (other == entity.get()) {
                gameStatics.entities--;
                return true;
            }
            return false;
        }), entityList.end());
    }

    void Update() {
        for (auto& e : entityList) {
            e->Update();
        }
    }

    void Render() {
        for (auto& e : entityList) {
            e->Render();
        }
    }

};






