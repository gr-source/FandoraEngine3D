#include "Camera.h"

Camera &Camera::MainCamera() {
    static Camera camera;
    return camera;
}

Camera::Camera()
    : position(Vector3(-22.098204f, 19.242348f, -27.375128f)),
      front(Vector3(0.0f, 0.0f, -1.0f)),
      up(Vector3(0.0f, 1.0f, 0.0f)),
      worldUp(Vector3(0.0f, 1.0f, 0.0f)),
      yaw(51.900005),
      pitch(-24.600000),
      movementSpeed(30.0f),
      mouseSensitivity(0.1f)
{
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    const Vector3 newFront{
        std::cos(Global::Radians(yaw)) * std::cos(Global::Radians(pitch)),
        std::sin(Global::Radians(pitch)),
        std::sin(Global::Radians(yaw)) * std::cos(Global::Radians(pitch))
    };

    front = newFront.normalize();

    right = Vector3::Normalize(Vector3::Cross(front, worldUp));
    up = Vector3::Normalize(Vector3::Cross(right, front));
}

Matrix4x4 Camera::getViewMatrix() const {
    return Matrix4x4::LookAtMatrix(position, position + front, up);
}

void Camera::processKeyboardInput(int key, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (key == GLFW_KEY_W) // Forward
        position += front * velocity;
    if (key == GLFW_KEY_S) // Backward
        position -= front * velocity;
    if (key == GLFW_KEY_A) // Left
        position -= right * velocity;
    if (key == GLFW_KEY_D) // Right
        position += right * velocity;
}

void Camera::processMouseMovement(const Vector2& lhs) {
    const Vector2 sensi = lhs * mouseSensitivity;

    if (std::abs(sensi.x) > 0.1f || std::abs(sensi.y) > 0.1f) {
        pitch += -sensi.y;
        yaw += sensi.x;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        if (yaw > 360.0f)
            yaw -= 360.0f;
        if (yaw < 0.0f)
            yaw += 360.0f;

        updateCameraVectors();
    }
}

