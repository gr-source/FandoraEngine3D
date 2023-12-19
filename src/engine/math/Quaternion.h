#pragma once

#include "Vector3.h"

#include <cmath>

struct Quaternion {
    float w;
    float x;
    float y;
    float z;

    Quaternion(float w = 0.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f) : w(w), x(x), y(y), z(z) {}

    static Quaternion LookRotation(const Vector3& forward, const Vector3& up) {
        Vector3 right = Vector3::Cross(up, forward);
        Vector3 normalizedRight = Vector3::Normalize(right);

        Vector3 newUp = Vector3::Cross(forward, normalizedRight);

        float trace = 1.0f + Vector3::Dot(normalizedRight, up + forward);
        float s;

        Quaternion result;

        if (trace > 0.0001f) {
            s = 0.5f / std::sqrt(trace);
            result.w = 0.25f / s;
            result.x = (up.z - forward.y) * s;
            result.y = (forward.x - normalizedRight.z) * s;
            result.z = (normalizedRight.y - up.x) * s;
        } else {
            if (normalizedRight.x > normalizedRight.y && normalizedRight.x > newUp.x) {
                s = 2.0f * std::sqrt(1.0f + normalizedRight.x - up.y - forward.z);
                result.w = (up.z - forward.y) / s;
                result.x = 0.25f * s;
                result.y = (up.x + normalizedRight.y) / s;
                result.z = (forward.x + normalizedRight.z) / s;
            } else if (normalizedRight.y > newUp.y) {
                s = 2.0f * std::sqrt(1.0f + up.y - normalizedRight.x - forward.z);
                result.w = (forward.x - normalizedRight.z) / s;
                result.x = (up.x + normalizedRight.y) / s;
                result.y = 0.25f * s;
                result.z = (forward.y + newUp.z) / s;
            } else {
                s = 2.0f * std::sqrt(1.0f + forward.z - normalizedRight.x - up.y);
                result.w = (normalizedRight.y - up.x) / s;
                result.x = (forward.x + normalizedRight.z) / s;
                result.y = (forward.y + newUp.z) / s;
                result.z = 0.25f * s;
            }
        }

        return result;
    }
};








