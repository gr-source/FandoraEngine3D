#pragma once

#include "Global.h"

class Camera {
private:
    Vector3 front;
    Vector3 up;
    Vector3 right;
    Vector3 worldUp;

    float movementSpeed;
    float mouseSensitivity;

    void updateCameraVectors();

public:
    Vector3 position;
    float yaw;
    float pitch;

    static Camera& MainCamera();
    
    Camera();

    Matrix4x4 getViewMatrix() const;
    void processKeyboardInput(int direction, float deltaTime);
    void processMouseMovement(const Vector2& lhs);

};