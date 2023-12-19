#pragma once

#include "Global.h"


class Light {
public:
    Vector3 position;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;

    Light(const Vector3& position = Vector3(0.0f, 0.0f, 0.0f), const Vector3& ambient = Vector3(0.80f, 0.80f, 0.80f), const Vector3& diffuse = Vector3(1.0f, 1.0f, 1.0f), const Vector3& specular = Vector3(1.0f, 1.0f, 1.0f));

    static Light& GetSun();
};

