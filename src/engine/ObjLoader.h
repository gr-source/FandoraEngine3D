#pragma once

#include "Global.h"

struct ObjLoader {
    std::vector<Vector2> uvList;
    std::vector<Vector3> normalList;
    std::vector<Vector3> vertexList;

    std::vector<Vector3> normalIndices;
    std::vector<Vector3> vertexIndices;
    std::vector<Vector2> uvIndices;
    std::vector<GLuint> indices;
    std::shared_ptr<Texture> texture;

    bool hasObjtLoad;

    ObjLoader(const std::string& obj);
    ~ObjLoader();

private:
    void clear();

    void Load(std::stringstream& ss);
    void LoadMtl(std::string ss);

    const Vector3 getVertices(std::stringstream& ss) const;
    const Vector2 getTextCoord(std::stringstream& ss) const;
    const Vector3 getNormal(std::stringstream& ss) const;
protected:
    ObjLoader() = default;
};

