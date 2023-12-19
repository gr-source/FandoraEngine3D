#include "Global.h"
#include "Shader.h"
#include "Screen.h"
#include "Camera.h"
#include "Material.h"
#include "GameObject.h"

#include "ObjLoader.h"

#include "component/Transform.h"

void APIENTRY Global::DebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
    return;
    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;
    
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
}

float Global::Radians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

bool Global::IsStartWith(const std::string& source, const std::string& text) {
    if (source.empty() || text.empty()) return false;
    
    int sLen = text.length();

    std::string result = source.substr(0, sLen);

    return result == source;
}

bool Global::IsEndWith(const std::string& source, const std::string& text) {
    if (source.empty() || text.empty()) return false;

    int sLen = text.length();

    std::string result = source.substr(source.length() - sLen, sLen);

    return result == source;
}

bool Global::IsContains(const std::string& source, const std::string& text) {
    if (source.empty() || text.empty()) return false;

    std::size_t npos = source.find(text);

    return npos != std::string::npos;
}

bool Global::IsEquals(const std::string& source1, const std::string& source2) {
    return source1 == source2;
}

