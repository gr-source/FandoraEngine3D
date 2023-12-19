#pragma once

#include "Global.h"

class Material {
public:
    std::string name;

    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float shininess;

    Color color;
    std::shared_ptr<Texture> texture;
    float scale;

    Material(const std::string& name) : name(name), ambient(Vector3(1.0f, 1.0f, 1.0f)), diffuse(Vector3(0.8f, 0.8f, 0.8f)), specular(Vector3(1.0f, 1.0f, 1.0f)), shininess(32.0f), scale(1.0f) {}

    Material(
        const Vector3& ambient = Vector3(1.0f, 1.0f, 1.0f),
        const Vector3& diffuse = Vector3(0.8f, 0.8f, 0.8f),
        const Vector3& specular = Vector3(1.0f, 1.0f, 1.0f),
        float shininess = 32.2f
    ) : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), scale(1.0f) {}

};

