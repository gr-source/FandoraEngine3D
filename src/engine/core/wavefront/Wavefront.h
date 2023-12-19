#pragma once 

#include "../../Global.h"

#include "Object.h"

class Wavefront {
public:
    std::unordered_map<std::string, std::unique_ptr<Material>> materials;
    std::vector<Object> objects;

    Wavefront(const std::string& path);
private:
    void loadMaterial(std::string& path);
    void loadFaces(std::istream& is);

    Vector3 getVertice(std::istream& is);
    Vector3 getNormal(std::istream& is);
    Vector2 getUv(std::istream& is);

    std::vector<Vector3> tempVertices;
    std::vector<Vector3> tempNormal;
    std::vector<Vector2> tempUv;
};

