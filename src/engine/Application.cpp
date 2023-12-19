#include "Application.h"

void Application::Quit() {
    GLFWwindow* window = glfwGetCurrentContext();
    if (window) {
        glfwDestroyWindow(window);
    }
    
    glfwTerminate();


    exit(EXIT_SUCCESS);
}

void Application::Quit(const std::string& message) {
    GLFWwindow* window = glfwGetCurrentContext();
    if (window) {
        glfwDestroyWindow(window);
    }
    
    glfwTerminate();

    std::cerr << message << std::endl;

    exit(EXIT_SUCCESS);
}



