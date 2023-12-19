#include "Resources.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "ObjLoader.h"
#include "GameObject.h"

#include "component/Transform.h"
#include "component/MeshRender.h"

#include "core/wavefront/Wavefront.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

template <>
Texture& Resources::Load<Texture>(const std::string& path) {
    if (!std::filesystem::exists(path)) {
        throw new Exception("file not found: " + path);
    }

    int width, height, nrChannels;
    stbi_uc *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        throw new Exception("stbi_load error");
    }

    GLuint textureID;

    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);
    {
        GLenum format = (nrChannels == 3) ? GL_RGB : GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //Repetir imagem
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        //Abilitar uma imagem mais bonita(tipo longe deixa mais embaçada perto melhor qualidade)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    Texture* texture = new Texture(textureID);

    return *texture;
}

template <>
GameObject& Resources::Load<GameObject>(const std::string& path) {
    std::unique_ptr<Wavefront> wavefront;
    if (String.endWith(path, ".obj")) {
        wavefront = std::make_unique<Wavefront>(path);
    }

    Object& object = wavefront->objects[0];

    GameObject* gameObject = new GameObject(object.name);
    gameObject->AddComponent<Transform>();
    gameObject->path = path;
    
    MeshRender& meshRender = gameObject->AddComponent<MeshRender>(object.mesh);
    if (object.material != nullptr) {
        meshRender.material = std::move(object.material);
    }
    return *gameObject;
}

template <>
Shader& Resources::Load<Shader>(const std::string& path) {
    std::string file = Global::IsContains(path, "/") ? path : "src/engine/shader/" + path;
    if (!std::filesystem::exists(file + ".vert")) {
        throw new Exception("vert file not found");
    }
    if (!std::filesystem::exists(file + ".frag")) {
        throw new Exception("frag file not found");
    }

    Shader* shader = new Shader(file + ".vert", file + ".frag");

    return *shader;
}

template <>
std::vector<std::unique_ptr<GameObject>> Resources::LoadAll<GameObject>(const std::string& path) {
    std::unique_ptr<Wavefront> wavefront;
    if (String.endWith(path, ".obj")) {
        wavefront = std::make_unique<Wavefront>(path);
    }

    std::vector<std::unique_ptr<GameObject>> list;

    for (const auto& object : wavefront->objects) {
        std::unique_ptr<GameObject> gameObject = std::make_unique<GameObject>(object.name);
        gameObject->AddComponent<Transform>();
        gameObject->path = path;
        
        MeshRender& meshRender = gameObject->AddComponent<MeshRender>(object.mesh);

        list.push_back(std::move(gameObject));
    }

    return list;
}
