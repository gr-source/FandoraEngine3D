
/*
    Criado: seg 13 nov 2023 11∶47∶36
    Atualizado: qua 15 nov 2023 11∶23∶54
    By: ghosth-br
*/


#pragma once

#include <map>
#include <array>
#include <mutex>
#include <string>
#include <memory>
#include <vector>
#include <thread>
#include <fstream>
#include <ostream>
#include <istream>
#include <iostream>
#include <algorithm>
#include <filesystem>

#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ui/imgui/backends/imgui_impl_opengl3.h"
#include "ui/imgui/backends/imgui_impl_glfw.h"
#include "ui/imgui/imgui.h"

#include "math/Matrix4x4.h"
#include "Color.h"
#include "ECS.h"
#include "Log.h"

#include "core/exception/Exception.h"

class Game;

class Mesh;
class Light;
class Camera;
class Shader;
class Texture;
class Material;
class GameObject;
class FrameBuffer;

class Transform;

class ImGuiRender;

class SceneManager;
class Scenes;

extern std::vector<std::unique_ptr<GameObject>> gameObjectList;
extern std::unique_ptr<FrameBuffer> mFrameBuffer;

enum ShaderType {
	DEFAULT,
	MESH,
	SCREEN
};


#define FILE_OBJ ".obj"
#define FILE_MTL ".mtl"

extern Manager manager;

extern std::unordered_map<ShaderType, std::shared_ptr<Shader>> mShaderMap;

enum PrimitiveType {
	Sphere,
	//Capsule,
	Cylinder,
	Cube,
	Plane,
	//Quad
	None
};

enum ImageType {
    ICON_FOLDER,
    ICON_FILE,
    ICON_BACK_FILE,
    ICON_GAMEOBJECT,
	ICON_PENCIL,
	ICON_LIGHT
};

namespace Global {
	extern void APIENTRY DebugCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam);
	extern void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	extern void DropCallback(GLFWwindow* window, int numFiles, const char** fileNames);
	extern void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
	extern void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	extern float Radians(float degrees);

	extern bool IsStartWith(const std::string& source, const std::string& text);
	extern bool IsEndWith(const std::string& source, const std::string& text);
	extern bool IsContains(const std::string& source, const std::string& text);
	extern bool IsEquals(const std::string& source1, const std::string& source2);
}

struct {
	bool equals(const std::string& text, const std::string& last) {
		return text == last;
	};

	bool contains(const std::string& text, const std::string& last) {
		if (text.empty() || last.empty()) return false;

		std::size_t npos = text.find(last);

		return npos != std::string::npos;
	}

	bool endWith(const std::string& text, const std::string& last) {
		if (text.empty() || last.empty()) return false;

		int len = last.length();

		std::string result = text.substr(text.length() - len, len);

		return result == last;
	}
} String;

