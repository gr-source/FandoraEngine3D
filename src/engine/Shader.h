#pragma once

/*
    Criado: seg 13 nov 2023 11∶50∶06
    Atualizado: qui 23 nov 2023 12∶23∶46
    by: ghost-br
*/

#include "Global.h"

class Shader {
public:

    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    Shader() = default;

    void bind();
    void setUniform(const char* name, const Matrix4x4& value);
    void setUniform(const char* name, const Vector3& value);
    void setUniform(const char* name, const Color& value);
    void setUniform(const char* name, float value);
    void setUniform(const char* name, int value);
    void unbind();

    ~Shader();
    
    GLuint programID;
    
private:
    std::string vertextPath;
    std::string fragmentPath;
    std::vector<GLuint> bufferList;

    std::string loadFile(const std::string& path);

    void checkError(GLuint shaders);
};

