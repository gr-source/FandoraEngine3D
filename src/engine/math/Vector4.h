#pragma once

struct Vector4 {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float data[4];
    };

    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
};