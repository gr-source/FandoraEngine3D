#pragma once

struct Vector3 {
    union {
        struct {
            float x;
            float y;
            float z;
        };
        float data[3];
    };

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    Vector3(const Vector3& other) {
        *this = other;
    }

    Vector3 normalize() const {
        float len = magnitude();

        if (len != 0.0f) {
            return Vector3(x / len, y / len, z / len);
        } else {
            return Vector3::Zero();
        }
    }

    static Vector3 Normalize(const Vector3& other) {
        float len = other.magnitude();

        if (len != 0.0f) {
            return Vector3(other.x / len, other.y / len, other.z / len);
        } else {
            return Vector3::Zero();
        }
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    static Vector3 Cross(const Vector3& a, const Vector3& b) {
        return Vector3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    float Dot(const Vector3& v2) const {
        return x * v2.x + y * v2.y + z * v2.z;
    }

    static float Dot(const Vector3& v1, const Vector3& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    float magnitude() const {
        return (float)std::sqrt(x * x + y * y + z * z);
    }

    Vector3 operator -(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    Vector3 operator -(float other) const {
        return Vector3(x - other, y - other, z - other);
    }

    Vector3 operator +(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator +(float other) const {
        return Vector3(x + other, y + other, z + other);
    }

    Vector3 operator *(const Vector3& other) const {
        return Vector3(x * other.x, y * other.y, z * other.z);
    }

    Vector3 operator *(float other) const {
        return Vector3(x * other, y * other, z * other);
    }

    Vector3& operator +=(const Vector3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3& operator +=(float other) {
        x += other;
        y += other;
        z += other;     
        return *this;
    }

    Vector3& operator -=(const Vector3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3& operator -=(float other) {
        x -= other;
        y -= other;
        z -= other;
        return *this;
    }

    bool operator==(const Vector3& other) const {
        return ((x == other.x) && (y == other.y) && (z == other.z));
    }

    bool operator!=(const Vector3& other) const {
        return ((x != other.x) && (y != other.y) && (z != other.z));
    }

    Vector3& operator=(const Vector3& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    friend std::istream& operator >>(std::istream& is, Vector3& other) {
        is >> other.x >> other.y >> other.z;
        return is;
    }
    
    friend std::ostream& operator <<(std::ostream& os, const Vector3& other) {
        os << other.x << " " << other.y << " " << other.z;
        return os;
    }
    
    static Vector3 Zero() {
        return Vector3(0.0f, 0.0f, 0.0f);
    }

    static Vector3 One() {
        return Vector3(1.0f, 1.0f, 1.0f);
    }

    static Vector3 Forward() {
        return Vector3(0.0f, 0.0f, 1.0f);
    }

    static Vector3 Up() {
        return Vector3(0.0f, 1.0f, 0.0f);
    }
};