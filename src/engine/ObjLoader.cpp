#include "ObjLoader.h"

#include "Resources.h"
#include "Texture.h"

ObjLoader::ObjLoader(const std::string& objPath) : hasObjtLoad(false) {
    std::ifstream fileObj(objPath, std::ios::in);
    
    if (!fileObj.is_open()) {
        std::cerr << "(OBJ) file not found! " << objPath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(fileObj, line)) {
        std::stringstream ss(line);

        std::string name;

        if (!(ss >> name)) {
            continue;
        }

        if (Global::IsEquals(name, "mtllib")) {
            std::string mtl;

            if (!(ss >> mtl)) {
                continue;
            }
            LoadMtl(mtl);

        } else if (Global::IsEquals(name, "v")) {
            vertexList.emplace_back(getVertices(ss));
        } else if (Global::IsEquals(name, "vt")) {
            uvList.emplace_back(getTextCoord(ss));
        } else if (Global::IsEquals(name, "vn")) {
            normalList.emplace_back(getNormal(ss));
        } else if (Global::IsEquals(name, "f")) {
            Load(ss);
        }
    }
    fileObj.close();

    hasObjtLoad = true;
}

ObjLoader::~ObjLoader() {
    clear();
}

void ObjLoader::clear() {
    if (!uvList.empty()) {
        uvList.clear();
    }
    if (!normalList.empty()) {
        normalList.clear();
    }
    if (!vertexList.empty()) {
        vertexList.clear();
    }
    if (!normalIndices.empty()) {
        normalIndices.clear();
    }
    if (!vertexIndices.empty()) {
        vertexIndices.clear();
    }
    if (!indices.empty()) {
        indices.clear();
    }
}

void ObjLoader::Load(std::stringstream& ss) {
    int vertexIndex = 0, textureIndex = 0, normalIndex = 0;

    char delimiter;

    while ((ss >> vertexIndex >> delimiter >> textureIndex >> delimiter >> normalIndex)) {
        normalIndices.push_back(normalList[normalIndex - 1]);
        vertexIndices.push_back(vertexList[vertexIndex - 1]);
        uvIndices.push_back(uvList[textureIndex - 1]);

        indices.push_back(vertexIndex -1);
    }
}

void ObjLoader::LoadMtl(std::string path) {
    std::fstream mtlFile("src/assets/gameObject/" + path, std::ios::in);
    if (!mtlFile.is_open()) {
        std::cerr << "Mtl file not found" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(mtlFile, line)) {
        std::stringstream ss(line);

        std::string name;

        if (!(ss >> name)) {
            continue;
        }

        if (Global::IsEquals(name, "map_Kd")) {
            std::string path;

            if (!(ss >> path)) {
                continue;
            }
            std::cout << path << std::endl;
            texture = std::shared_ptr<Texture>(&Resources::Load<Texture>(path));
        }
    }
    mtlFile.close();
}

const Vector3 ObjLoader::getVertices(std::stringstream& ss) const {
    Vector3 results;

    if (!(ss >> results.x >> results.y >> results.z)) {
        return results;
    }
    return results;
}

const Vector2 ObjLoader::getTextCoord(std::stringstream& ss) const {
    Vector2 results;

    if (!(ss >> results.x >> results.y)) {
        return results;
    }
    return results;
}

const Vector3 ObjLoader::getNormal(std::stringstream& ss) const {
    Vector3 results;

    if (!(ss >> results.x >> results.y >> results.z)) {
        return results;
    }
    return results;
}
