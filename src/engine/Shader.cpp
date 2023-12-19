#include "Shader.h"

#include "Light.h"
#include "Material.h"

Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile) : vertextPath(vertexFile), fragmentPath(fragmentFile) {
    std::string contentVertex = loadFile(vertexFile);
    std::string contentFragment = loadFile(fragmentFile);

    const char* vertextSource = contentVertex.c_str();
    const char* fragmentSource = contentFragment.c_str();

    programID = glCreateProgram();
    GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexID, 1, &vertextSource, nullptr);
    glShaderSource(fragmentID, 1, &fragmentSource, nullptr);

    glCompileShader(vertexID);
    checkError(vertexID);

    glCompileShader(fragmentID);
    checkError(fragmentID);

    glAttachShader(programID, vertexID);
    glAttachShader(programID, fragmentID);

    glLinkProgram(programID);

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

void Shader::bind() {
    glUseProgram(programID);
}

void Shader::setUniform(const char* name, const Matrix4x4& value) {
    GLuint location =  glGetUniformLocation(programID, name);
    if (location != GL_INVALID_INDEX) {
        glUniformMatrix4fv(location, 1, GL_FALSE, value.data);
    }
}

void Shader::setUniform(const char* name, const Vector3& value) {
    GLuint location =  glGetUniformLocation(programID, name);
    if (location != GL_INVALID_INDEX) {
        glUniform3fv(location, 1, value.data);
    }
}

void Shader::setUniform(const char* name, const Color& value) {
    GLuint location =  glGetUniformLocation(programID, name);
    if (location != GL_INVALID_INDEX) {
        glUniform3fv(location, 1, value.data);
    }
}

void Shader::setUniform(const char* name, float value) {
    GLuint location =  glGetUniformLocation(programID, name);
    if (location != GL_INVALID_INDEX) {
        glUniform1f(location, value);
    }
}

void Shader::setUniform(const char* name, int value) {
    GLuint location =  glGetUniformLocation(programID, name);
    if (location != GL_INVALID_INDEX) {
        glUniform1i(location, value);
    }
}

void Shader::unbind() {
    glUseProgram(0);
}

Shader::~Shader() {
    glDeleteBuffers(bufferList.size(), bufferList.data());
    
    if (programID) {
        glDeleteProgram(programID);
    }
}

std::string Shader::loadFile(const std::string& path) {
    std::fstream file(path, std::ios::in);
    if (!file.is_open()) {
        std::cout << "File not found: " << path << std::endl;
        return nullptr;
    }
    std::string content ((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return content;
}

void Shader::checkError(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        GLint type;
        glGetShaderiv(shader, GL_SHADER_TYPE, &type);

        char* logMessage = new char[length];

        glGetShaderInfoLog(shader, length, NULL, logMessage);

        if (type == GL_FRAGMENT_SHADER) {
            std::cout << "Shader compilation failed. (GL_FRAGMENT_SHADER): \n" << logMessage << std::endl;
        } else {
            std::cout << "Shader compilation failed. (GL_VERTEX_SHADER):\n" << logMessage << std::endl;
        }
        delete[] logMessage;
    }
}