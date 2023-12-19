#pragma once

#include "../ECS.h"
#include "../Global.h"

class Transform : public Component {
private:
public:
    Vector3 position;
    Vector3 scale;
    
    Quaternion rotation;

    Matrix4x4 localToWorldMatrix;

    Transform(const Vector3& position = Vector3::Zero(), const Vector3& scale = Vector3::One()) : localToWorldMatrix(Matrix4x4::identityMatrix), position(position), scale(scale) {}

    /*
    void rotateY(float angle) {
        localToWorldMatrix.rotateY(angle);
    }
    */

    Matrix4x4& getLocalMatrix() {
        localToWorldMatrix.translate(position);
        localToWorldMatrix.scale(scale);

        return localToWorldMatrix;
    }

    std::unique_ptr<Component> Clone() override {
        return std::make_unique<Transform>(*this);
    }
};



