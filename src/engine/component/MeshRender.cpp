#include "MeshRender.h"

#include "../ECS.h"
#include "../Mesh.h"
#include "../Light.h"
#include "../Global.h"
#include "../Camera.h"
#include "../Shader.h"
#include "../Screen.h"
#include "../Texture.h"
#include "../Material.h"
#include "../GameObject.h"
#include "../Resources.h"

#include "Transform.h"

GameStatics gameStatics;

MeshRender::MeshRender(const Mesh& mesh) {
    vertices = mesh.vertices.size();
    
    gameStatics.vertices += mesh.vertices.size();

    shader = std::move(std::shared_ptr<Shader>(&Resources::Load<Shader>("ShaderMain")));
   
    Matrix4x4 matrix4x4 = Matrix4x4::identityMatrix;

    std::size_t size = sizeof(Matrix4x4) + sizeof(Vector3) * mesh.vertices.size() + sizeof(Vector3) * mesh.normals.size() + sizeof(Vector2) * mesh.uv.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    GLintptr offset = 0;
    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Matrix4x4), &matrix4x4);
    offset += sizeof(Matrix4x4);

    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vector3) * mesh.vertices.size(), mesh.vertices.data());
    offset += sizeof(Vector3) * mesh.vertices.size();

    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vector3) * mesh.normals.size(), mesh.normals.data());
    offset += sizeof(Vector3) * mesh.normals.size();

    glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Vector2) * mesh.uv.size(), mesh.uv.data());
    offset += sizeof(Vector2) * mesh.uv.size();

    glBindVertexArray(VAO);
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), reinterpret_cast<void*>(sizeof(Matrix4x4)));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), reinterpret_cast<void*>(sizeof(Matrix4x4) + sizeof(Vector3) * mesh.vertices.size()));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), reinterpret_cast<void*>(sizeof(Matrix4x4) + sizeof(Vector3) * mesh.vertices.size() + sizeof(Vector3) * mesh.normals.size()));
        glEnableVertexAttribArray(2);

        for (unsigned int i = 0; i < 4; ++i) {
            glEnableVertexAttribArray(3 + i);
            glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(Matrix4x4), reinterpret_cast<void*>(sizeof(GLfloat) * i * 4));
            glVertexAttribDivisor(3 + i, 1);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void MeshRender::Start() {
    transform = &entity->GetComponent<Transform>();
    camera = &Camera::MainCamera();
}

void MeshRender::Render() {
    const Light& sun = Light::GetSun();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Matrix4x4), &transform->getLocalMatrix());

    Matrix4x4 view = camera->getViewMatrix();
    static const Matrix4x4 projection = Matrix4x4::Perspective(Global::Radians(60.0f), (GLfloat)Screen::width / (GLfloat)Screen::height, 0.1f, 100.0f);

    shader->bind();
    
    //Matrix4x4 pv = projection * view;
   // Matrix4x4 pv = view * projection;

    shader->setUniform("viewPos", camera->position);
    //shader->setUniform("pv", pv);
    shader->setUniform("view", view);
    shader->setUniform("projection", projection);

    if (material->texture != nullptr) {
        material->texture->bind(GL_TEXTURE0);
        shader->setUniform("material.hasTexture", true);
        shader->setUniform("material.texture", 0);
        shader->setUniform("scale", material->scale);
    }
    
    shader->setUniform("material.ambient",   material->ambient);
    shader->setUniform("material.diffuse",   material->diffuse);
    shader->setUniform("material.specular",  material->specular);
    shader->setUniform("material.shininess", material->shininess);
    shader->setUniform("material.color",     material->color);

    shader->setUniform("dirLight.ambient",  sun.ambient);
    shader->setUniform("dirLight.diffuse",  sun.diffuse);
    shader->setUniform("dirLight.specular", sun.specular);

    shader->setUniform("dirLight.direction", sun.position);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

std::unique_ptr<Component> MeshRender::Clone() {
    return std::make_unique<MeshRender>(*this);
}

MeshRender::~MeshRender() {
}
