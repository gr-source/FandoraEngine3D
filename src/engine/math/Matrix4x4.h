#pragma once

#include <array>
#include <cmath>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"

struct Matrix4x4 {
    union {
        struct {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };
        float data[16];
    };

    
    Matrix4x4(float m00 = 1.0f, float m01 = 0.0f, float m02 = 0.0f, float m03 = 0.0f, float m10 = 0.0f, float m11 = 1.0f, float m12 = 0.0f, float m13 = 0.0f, float m20 = 0.0f, float m21 = 0.0f, float m22 = 1.0f, float m23 = 0.0f, float m30 = 0.0f, float m31 = 0.0f, float m32 = 0.0f, float m33 = 1.0f)
        : m00(m00), m01(m01), m02(m02), m03(m03),
          m10(m10), m11(m11), m12(m12), m13(m13),
          m20(m20), m21(m21), m22(m22), m23(m23),
          m30(m30), m31(m31), m32(m32), m33(m33) {
    }
    
    static const Matrix4x4 Perspective(float fovy, float aspect, float zNear, float zFar) {
        float tanHalfFovy = std::tan(fovy / 2.0f);
        if (tanHalfFovy <= 0.0f) tanHalfFovy = std::numeric_limits<float>::epsilon();

        Matrix4x4 result = Matrix4x4::identityMatrix;
        result.m00 = 1.0f / (aspect * tanHalfFovy);

        result.m11 = 1.0f / (tanHalfFovy);

        result.m22 = (zFar + zNear) / (zNear - zFar);
        result.m23 = -1.0f;

        result.m32 = (2.0f * zFar * zNear) / (zFar - zNear);
        return result;
    }

    static const Matrix4x4 LookAtMatrix(const Vector3& eye, const Vector3& center, const Vector3& upward) {
        const Vector3 forward = Vector3::Normalize(center - eye);
        const Vector3 right = Vector3::Normalize(Vector3::Cross(forward, upward));
        const Vector3 up = Vector3::Cross(right, forward);

        Matrix4x4 result = Matrix4x4::identityMatrix;
        result.m00 = right.x;
        result.m01 = up.x;
        result.m02 = -forward.x;

        result.m10 = right.y;
        result.m11 = up.y;
        result.m12 = -forward.y;

        result.m20 = right.z;
        result.m21 = up.z;
        result.m22 = -forward.z;

        result.m30 = -Vector3::Dot(right, eye);
        result.m31 = -Vector3::Dot(up, eye);
        result.m32 = Vector3::Dot(forward, eye);

        return result;
    }

    void translate(const Vector3& translation) {
        m30 = translation.x;
        m31 = translation.y;
        m32 = translation.z;
    }

    static const Matrix4x4 Translate(const Vector3& position) {
        Matrix4x4 result = Matrix4x4::identityMatrix;
        result.m03 = position.x;
        result.m13 = position.y;
        result.m23 = position.z;
        return result;
    }

    void scale(const Vector3& scaling) {
        m00 = scaling.x;
        m11 = scaling.y;
        m22 = scaling.z;
    }

    Matrix4x4 operator *(const Matrix4x4& other) const {
        Matrix4x4 result;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += this->data[i * 4 + k] * other.data[k * 4 + j];
                }
                result.data[i * 4 + j] = sum;
            }
        }

        return result;
    }

    Matrix4x4& operator =(const Matrix4x4& other) {
        if (this != &other) {
            m00 = other.m00; m01 = other.m01; m02 = other.m02; m03 = other.m03;
            m10 = other.m10; m11 = other.m11; m12 = other.m12; m13 = other.m13;
            m20 = other.m20; m21 = other.m21; m22 = other.m22; m23 = other.m23;
            m30 = other.m30; m31 = other.m31; m32 = other.m32; m33 = other.m33;
        }
        return *this;
    }
    static const Matrix4x4 zeroMatrix;
    static const Matrix4x4 identityMatrix;
};




