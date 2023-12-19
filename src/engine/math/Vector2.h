#pragma once

#include <istream>
#include <ostream>

struct Vector2 {
    union {
        struct {
            float x;
            float y;
        };
        float data[2];
    };

    Vector2(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Vector2(const Vector2& other) {
        *this = other;
    }

    Vector2 operator /(const Vector2& other) const {
        return {x / other.x, y / other.y};
    }

    Vector2 operator /(float other) const {
        return {x / other, y / other};
    }

    Vector2 operator -(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator -(float other) const {
        return {x - other, y - other};
    }

    Vector2 operator *(const Vector2& other) const {
        return {x * other.x, y * other.y};
    }

    Vector2 operator *(float other) const {
        return {x * other, y * other};
    }

    Vector2& operator =(const Vector2& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    bool operator !=(const Vector2& other) {
        return ((x != other.x) && (y != other.y));
    }
    
    friend std::istream& operator >>(std::istream& is, Vector2& other) {
        is >> other.x >> other.y;
        return is;
    }
    
    friend std::ostream& operator <<(std::ostream& os, const Vector2& other) {
        os << other.x << " " << other.y;
        return os;
    }
};
