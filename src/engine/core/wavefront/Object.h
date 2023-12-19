#pragma once

#include "../../Material.h"
#include "../../Global.h"
#include "../../Mesh.h"

struct Object {
    std::string name;
    std::unique_ptr<Material> material;
    Mesh mesh;

    Object(const std::string& name) : name(name), material(std::make_unique<Material>("Default")) {}
};
