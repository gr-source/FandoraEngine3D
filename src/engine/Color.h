#pragma once

struct Color {
    union {
        struct {
            float r;
            float g;
            float b;
            float a;
        };
        float data[4];
    };

    Color(float r = 255, float g = 255, float b = 255, float a = 255) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {}

    Color(const Color& other) {
        *this = other;
    }

    static Color Red() {
        return {255.0f, 0.0f, 0.0f};
    };

    static Color Green() {
        return {0.0f, 255.0f, 0.0f};
    };

    static Color Blue() {
        return {0.0f, 0.0f, 255.0f};
    };

    static Color White() {
        return {255.0f, 255.0f, 255.0f};
    };

    static Color Black() {
        return {0.0f, 0.0f, 0.0f};
    };

    Color& operator=(const Color& other) {
        if (this != &other) {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
        }
        return *this;
    }
};

