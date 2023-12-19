#include "Time.h"
#include "Global.h"

float Time::deltaTime = 0.0f;
int Time::FPS = 60;

void Time::Tick() {
    const float targetFrameTime = 1.0f / FPS;

    static double lastTime = glfwGetTime();

    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;

    if (deltaTime < targetFrameTime) {
        double sleepTime = targetFrameTime - deltaTime;

        if (sleepTime > 0.0) {
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(sleepTime * 1000000.0)));
        }

        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
    }

    lastTime = currentTime;
}

