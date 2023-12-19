#pragma once 

#include "Transform.h"

#include "../Global.h"
#include "../Light.h"

class SunComponent : public Component {
private:
    Light* sunLight;
    Transform* transform;
public:
    SunComponent() = default;
    
    void Start() override {
        sunLight = &Light::GetSun();
        transform = &entity->GetComponent<Transform>();
    }

    void Update() override {
        static Vector3 lastPosition = transform->position;
        if (lastPosition != transform->position) {
            sunLight->position = transform->position;
            lastPosition = transform->position;
        }
    }
};

