#pragma once

<<<<<<< HEAD:src/core/math.hpp
=======
#define SHOGUN_PI	3.1415926535897932 // first 16 digits
#define SHOGUN_RAD	SHOGUN_PI / 180.0  // convert degrees to radians by multiplying them by this

#define AVMATH_GLM_INTEGRATION

>>>>>>> 4c635c76473887c6cd7d030e545adc4f573272ce:src/core/vector.hpp
#include <cmath>
#include <stdlib.h>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    Vector2 operator+(Vector2 v) const;
    void operator+=(Vector2 v);

    Vector2 operator+(float f) const;
    void operator+=(float f);

    Vector2 operator-(Vector2 v) const;
    void operator-=(Vector2 v);

    Vector2 operator-(float f) const;
    void operator-=(float f);

    Vector2 operator*(Vector2 v) const;
    void operator*=(Vector2 v);

    Vector2 operator*(float f) const;
    void operator*=(float f);

    Vector2 operator/(Vector2 v) const;
    void operator/=(Vector2 v);

    Vector2 operator/(float f) const;
    void operator/=(float f);

    float dot(Vector2 v2);
    float distance(Vector2 v2);
    float manhattanDistance(Vector2 v2);

    glm::vec2 glm() const;
    static Vector2 fromGLM(glm::vec2 vec);
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
    Vector3 normalize();
    Vector3 negate() const;
    Vector3 invert() const;
    Vector3 abs() const;
    Vector3 square() const;
    Vector3 radians() const;

    Vector3 operator+(Vector3 v) const;
    void operator+=(Vector3 v);

    Vector3 operator+(float f) const;
    void operator+=(float f);

    Vector3 operator-(Vector3 v) const;
    void operator-=(Vector3 v);

    Vector3 operator-(float f) const;
    void operator-=(float f);

    Vector3 operator*(Vector3 v) const;
    void operator*=(Vector3 v);

    Vector3 operator*(float f) const;
    void operator*=(float f);

    Vector3 operator/(Vector3 v) const;
    void operator/=(Vector3 v);

    Vector3 operator/(float f) const;
    void operator/=(float f);

    float dot(Vector3 v2) const;
    float angle(Vector3 v2) const;
    float distance(Vector3 v2) const;
    Vector3 cross(Vector3 v2) const;
    Vector3 reflect(Vector3 n) const;
    Vector3 project(Vector3 u) const;

    glm::vec3 glm() const;

    static Vector3 fromGLM(glm::vec3 vec);
};


inline std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    out << vec.x << " " << vec.y << " " << vec.z;
    return out;
}

inline std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
    out << vec.x << " " << vec.y;
    return out;
}

//Thanks Vetra for suggestion to move out of entity specific code
glm::mat4 calc_transform_matrix(const Vector3 position, const Vector3 rotation, const Vector3 scale);

} //End namespace SHOGUN
