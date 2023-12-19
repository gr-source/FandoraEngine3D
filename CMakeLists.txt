cmake_minimum_required(VERSION 3.0.0)
project(GameRenderGR VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(OpenGL_GL_PREFERENCE LEGACY)

add_executable(
    GameRenderGR
    
    src/main.cpp
    src/window/Game.cpp
    src/window/Window.cpp
    
    src/engine/Log.cpp
    src/engine/Mesh.cpp
    src/engine/Time.cpp
    src/engine/Light.cpp
    src/engine/Object.cpp
    src/engine/Shader.cpp
    src/engine/Camera.cpp
    src/engine/Global.cpp
    src/engine/Screen.cpp
    src/engine/Engine.cpp
    src/engine/Texture.cpp
    src/engine/Material.cpp
    src/engine/ObjLoader.cpp
    src/engine/Resources.cpp
    src/engine/GameObject.cpp
    src/engine/FrameBuffer.cpp
    src/engine/Application.cpp
    src/engine/math/Matrix4x4.cpp

    src/engine/noise/SimplexNoise.cpp

    src/engine/component/MeshRender.cpp

    src/engine/ui/ImGuiRender.cpp
    src/engine/ui/main/Template.cpp
    
    src/engine/core/scene/SceneManager.cpp
    src/engine/core/scene/Scene.cpp

    src/engine/core/wavefront/Wavefront.cpp
    
    src/engine/ui/imgui/backends/imgui_impl_opengl3.cpp
    src/engine/ui/imgui/backends/imgui_impl_glfw.cpp
    src/engine/ui/imgui/imgui_widgets.cpp
    src/engine/ui/imgui/imgui_tables.cpp
    src/engine/ui/imgui/imgui_demo.cpp
    src/engine/ui/imgui/imgui_draw.cpp
    src/engine/ui/imgui/imgui.cpp
)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("/home/idealrender/Documentos/FandoraEngine3D/src/engine/core/stb/")

target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${DIRECTORY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GLEW_LIBRARIES} glfw ${OPENGL_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
