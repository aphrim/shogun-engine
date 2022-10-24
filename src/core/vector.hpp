#pragma once

#define AVMATH_GLM_INTEGRATION

#include <cmath>
#include <stdlib.h>
#include <ostream>

#ifdef AVMATH_GLM_INTEGRATION
#include <glm/glm.hpp>
#endif

namespace SHOGUN {
class Vector2 {
public:
    float x;
    float y;

    Vector2(float x, float y);
    Vector2(float n);
    Vector2();

    float length() const;
    Vector2 normalize() const;
    Vector2 negate() const;
    Vector2 invert() const;
    Vector2 abs() const;
    Vector2 square() const;

    Vector2 operator+(Vector2 v);
    void operator+=(Vector2 v);

    Vector2 operator+(float f);
    void operator+=(float f);

    Vector2 operator-(Vector2 v);
    void operator-=(Vector2 v);

    Vector2 operator-(float f);
    void operator-=(float f);

    Vector2 operator*(Vector2 v);
    void operator*=(Vector2 v);

    Vector2 operator*(float f);
    void operator*=(float f);

    Vector2 operator/(Vector2 v);
    void operator/=(Vector2 v);

    Vector2 operator/(float f);
    void operator/=(float f);

    static float dot(Vector2 v1, Vector2 v2);
    static float distance(Vector2 v1, Vector2 v2);
    static float manhattanDistance(Vector2 v1, Vector2 v2);

#ifdef AVMATH_GLM_INTEGRATION
    glm::vec2 glm() const;
    static Vector2 fromGLM(glm::vec2 vec);
#endif
};

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z);
    Vector3(Vector2 v, float z);
    Vector3(float n);
    Vector3();

    float length() const;
    Vector3 normalize() const;
    Vector3 negate() const;
    Vector3 invert() const;
    Vector3 abs() const;
    Vector3 square() const;
    Vector3 radians() const;

    Vector3 operator+(Vector3 v);
    void operator+=(Vector3 v);

    Vector3 operator+(float f);
    void operator+=(float f);

    Vector3 operator-(Vector3 v);
    void operator-=(Vector3 v);

    Vector3 operator-(float f);
    void operator-=(float f);

    Vector3 operator*(Vector3 v);
    void operator*=(Vector3 v);

    Vector3 operator*(float f);
    void operator*=(float f);

    Vector3 operator/(Vector3 v);
    void operator/=(Vector3 v);

    Vector3 operator/(float f);
    void operator/=(float f);

    static float dot(Vector3 v1, Vector3 v2);
    static Vector3 cross(Vector3 v1, Vector3 v2);
    static float angle(Vector3 v1, Vector3 v2);
    static float distance(Vector3 v1, Vector3 v2);
    static Vector3 reflect(Vector3 v, Vector3 n);
    static Vector3 project(Vector3 v, Vector3 u);

#ifdef AVMATH_GLM_INTEGRATION
    glm::vec3 glm() const;

    static Vector3 fromGLM(glm::vec3 vec);
#endif
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    out << vec.x << " " << vec.y << " " << vec.z;
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
    out << vec.x << " " << vec.y;
    return out;
}

} //End namespace AE
