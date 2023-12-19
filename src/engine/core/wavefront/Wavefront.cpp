#include "Wavefront.h"

#include "../../Resources.h"
#include "../../Texture.h"

Wavefront::Wavefront(const std::string& path) {
    std::ifstream is(path);
    if (!is.is_open()) {
        throw std::runtime_error("Nonexistent file");
    }

    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        std::string token;

        if (!(iss >> token) || line.empty() || token.find("#") == 0) continue;

        if (token == "mtllib") { // material path
            std::string mtlPath;
            if (!(iss >> mtlPath)) {
                continue;
            }
            loadMaterial(mtlPath);
        } else if (token == "o") { // new object
            std::string name;
            if (!(iss >> name)) {
                continue;
            }
            objects.emplace_back(name);
        } else if (token == "v") { // vertice
            tempVertices.emplace_back(getVertice(iss)); // list
        } else if (token == "vn") { // normal
            tempNormal.emplace_back(getNormal(iss)); // list
        } else if (token == "vt") { // textcoord
            tempUv.emplace_back(getUv(iss)); // list
        } else if (token == "usemtl") { // use material in materiallib
            std::string name;
            if (!(iss >> name)) continue;

            auto& obj = objects.back();
            obj.material = std::move(materials[name]);
        } else if (token == "f") { // faces
            loadFaces(iss);
        }
    }

    is.close();
}

void Wavefront::loadFaces(std::istream& is) {
    auto& obj = objects.back();
    int verticeIndice = 0, uvIndice = 0, normalIndice = 0;

    char delimiter;

    while (is >> verticeIndice >> delimiter >> uvIndice >> delimiter >> normalIndice) {
        obj.mesh.vertices.emplace_back(tempVertices[verticeIndice - 1]);
        obj.mesh.normals.emplace_back(tempNormal[normalIndice - 1]);
        obj.mesh.uv.emplace_back(tempUv[uvIndice - 1]);
    }
}

void Wavefront::loadMaterial(std::string& path) {
    if (!String.contains(path, "/")) {
        path = "src/assets/gameObject/" + path;
    }

    std::fstream fs(path, std::ios::in);
    if (!fs.is_open()) {
        std::cerr << "Material file not found" << std::endl;
        return;
    }
    Material* current;

    std::string line;
    while (std::getline(fs, line)) {
        std::stringstream ss(line);

        std::string token;
        if (!(ss >> token) || line.empty() || String.contains(line, "#")) continue;

        if (token == "newmtl") {
            std::string name;
            if (!(ss >> name)) continue;

            current = new Material(name);

            materials.emplace(name, std::unique_ptr<Material>(current));
        }/* else if (token == "Ns") {
            // Processar Shininess (se necessário)
            if (!(ss >> current->shininess)) continue;
        } else if (token == "Ka") {
            if (!(ss >> current->ambient)) continue;
            // Processar Cor Ambiente (se necessário)
        } else if (token == "Kd") {
            // Processar Cor Difusa (se necessário)
            if (!(ss >> current->diffuse)) continue;
        } else if (token == "Ks") {
            // Processar Cor Especular (se necessário)
            if (!(ss >> current->specular)) continue;
        } else if (token == "Ke") {
            // Processar Cor Emissiva (se necessário)
        } else if (token == "Ni") {
            // Processar Índice de Refração (se necessário)
        } else if (token == "d") {
            // Processar Dissolver/Opacidade (se necessário)
        } */else if (token == "map_Kd") {
            std::string pathTexture;
            if (!(ss >> pathTexture)) continue;
            
            current->texture = std::move(std::unique_ptr<Texture>(&Resources::Load<Texture>(pathTexture)));
        } else if (token == "map_Ka") {
            // Processar Ambient Texture Map (se necessário)
        }
    }
    fs.close();
}


Vector3 Wavefront::getVertice(std::istream& is) {
    Vector3 result;

    if (!(is >> result)) {
        return result;
    }
    return result;
}

Vector3 Wavefront::getNormal(std::istream& is) {
    Vector3 result;

    if (!(is >> result)) {
        return result;
    }
    return result;
}

Vector2 Wavefront::getUv(std::istream& is) {
    Vector2 result;

    if (!(is >> result)) {
        return result;
    }
    return result;
}



