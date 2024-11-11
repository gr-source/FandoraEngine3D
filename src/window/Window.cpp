#include "Window.h"
#include "Game.h"

#include "../engine/Time.h"
#include "../engine/Global.h"
#include "../engine/Screen.h"
#include "../engine/Resources.h"
#include "../engine/Application.h"
#include "../engine/FrameBuffer.h"

#include "../engine/ui/ImGuiRender.h"

std::unique_ptr<FrameBuffer> mFrameBuffer;
std::unordered_map<ShaderType, std::shared_ptr<Shader>> mShaderMap;

Window::Window(const char *title, int screenWidth, int screenHeight) {
    Screen::SetResolution(screenWidth, screenHeight);

    if (glfwInit() != GLFW_TRUE) {
        Application::Quit("Error glfw nao iniciado");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(Screen::width, Screen::height, title, nullptr, nullptr);
    if (!window) {
        Application::Quit("Error ao cria o windown");
    }

    glfwSetFramebufferSizeCallback(window, Global::FrameBufferSizeCallback);
    glfwSetCursorPosCallback(window, Global::MouseCallback);
    glfwSetDropCallback(window, Global::DropCallback);
    glfwSetKeyCallback(window, Global::KeyCallback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        Application::Quit("Erro ao inicializar o GLEW");
    }
    srand(time(0));
    
    Start();
}

void Window::Start() {
    imGuiRender = std::make_unique<ImGuiRender>("#version 330 core");
    mFrameBuffer = std::make_unique<FrameBuffer>();

   // mShaderMap.emplace(ShaderType::DEFAULT, std::move(&Resources::Load<Shader>("default")));
   // mShaderMap.emplace(ShaderType::MESH,    std::move(&Resources::Load<Shader>("Mesh")));
   
    game = std::make_unique<Game>();
    game->Start();
    
    
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCullFace(GL_BACK);

    // Definindo o modo de renderização do polígono para GL_LINE (apenas linhas)
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    glDebugMessageCallback(Global::DebugCallback, nullptr);
}

void Window::Update() {
    Time::Tick();

    
    game->Update();
    
    // Usar framebuffer personalizado
    mFrameBuffer->bind();
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    game->Render();

    mFrameBuffer->unbind();

    // Restaurar o framebuffer principal e renderizar 2D ImGui usando a textura do framebuffer personalizado
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    // Inicia o ImGui
    imGuiRender->Begin();
    game->Gui();
    imGuiRender->End();
    /*
    */

    glfwSwapBuffers(window);
    glfwPollEvents();
}

bool Window::IsCloseWindow() const {
    return !glfwWindowShouldClose(window);
}

Window::~Window() {
    glfwDestroyWindow(window);
    
    glfwTerminate();
}

void Global::FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    Screen::SetResolution(static_cast<float>(width), static_cast<float>(height));

    mFrameBuffer->resize(width, height);

    glViewport(0, 0, width, height);
    glScissor(0, 0, width, height);
}
