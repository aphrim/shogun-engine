#include <cmath>
#include "Vector.hpp"

using namespace SHOGUN;

//Vector2
Vector2::Vector2(float x, float y) : x(x), y(y) {}
Vector2::Vector2(float n)          : x(n), y(n) {}
Vector2::Vector2()                 : x(0), y(0) {} 

float Vector2::length() const {
    return sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const {
    return *this / length();
}

Vector2 Vector2::negate() const{
    return Vector2(-x, -y);
}

Vector2 Vector2::invert() const{
    return Vector2(1/x, 1/y);
}

Vector2 Vector2::abs() const {
    return Vector2(std::abs(x), std::abs(y));
}

Vector2 Vector2::square() const{
    return Vector2(x * x, y * y);
}

Vector2 Vector2::operator+(Vector2 v) const {
    return Vector2(x + v.x, y + v.y);
}

void Vector2::operator+=(Vector2 v) {
    x += v.x;
    y += v.y;
}

Vector2 Vector2::operator+(float f) const {
    return Vector2(x + f, y + f);
}

void Vector2::operator+=(float f) {
    x += f;
    y += f;
}

Vector2 Vector2::operator-(Vector2 v) const {
    return Vector2(x - v.x, y - v.y);
}

void Vector2::operator-=(Vector2 v) {
    x -= v.x;
    y -= v.y;
}

Vector2 Vector2::operator-(float f) const {
    return Vector2(x - f, y - f);
}

void Vector2::operator-=(float f) {
    x -= f;
    y -= f;
}

Vector2 Vector2::operator*(Vector2 v) const {
    return Vector2(x * v.x, y * v.y);
}

void Vector2::operator*=(Vector2 v) {
    x *= v.x;
    y *= v.y;
}

Vector2 Vector2::operator*(float f) const {
    return Vector2(x * f, y * f);
}

void Vector2::operator*=(float f) {
    x *= f;
    y *= f;
}

Vector2 Vector2::operator/(Vector2 v) const {
    return (*this) * v.invert();
}

void Vector2::operator/=(Vector2 v) {
    (*this) *= v.invert();
}

Vector2 Vector2::operator/(float f) const {
    return (*this) * (1 / f);
}

void Vector2::operator/=(float f) {
    (*this) *= (1 / f);
}

float Vector2::dot(Vector2 v1, Vector2 v2) {
    return(v1.x * v2.x + v1.y * v2.y);
}

float Vector2::distance(Vector2 v1, Vector2 v2) {
    return (v1 - v2).length();
}

float Vector2::manhattanDistance(Vector2 v1, Vector2 v2) {
    Vector2 d = (v1 - v2).abs();
    return d.x + d.y;
}

#ifdef AVMATH_GLM_INTEGRATION
    glm::vec2 Vector2::glm() const {
        return glm::vec2(x, y);
    }

    Vector2 Vector2::fromGLM(glm::vec2 vec) {
        return Vector2(vec.x, vec.y);
    }
#endif

//Vector3

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {} 
Vector3::Vector3(Vector2 v, float z)        : x(v.x), y(v.y), z(z) {}
Vector3::Vector3(float n)                   : x(n), y(n), z(n) {}
Vector3::Vector3()                          : x(0), y(0), z(0) {}

Vector3 Vector3::operator/(Vector3 v) const {
    return (*this) * v.invert();
}

float Vector3::dot(Vector3 v1, Vector3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

float Vector3::length() const {
    return sqrt(dot(*this, *this)); // equivalent to sqrt(x^2 + y^2 + z^2)
}

Vector3 Vector3::normalize() {
	return *this / length();
}

Vector3 Vector3::negate() const {
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::invert() const {
    return Vector3(1/x, 1/y, 1/z);
}

Vector3 Vector3::abs() const {
    return Vector3(std::abs(x), std::abs(y), std::abs(z));
}

Vector3 Vector3::square() const {
    return Vector3(x * x, y * y, z * z);
}

Vector3 Vector3::radians() const {
    return Vector3(x * SHOGUN_RAD, y * SHOGUN_RAD, z * SHOGUN_RAD); 
}

Vector3 Vector3::operator+(Vector3 v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}


void Vector3::operator+=(Vector3 v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3 Vector3::operator+(float f) const {
    return Vector3(x + f, y + f, z + f);
}

void Vector3::operator+=(float f) {
    x += f;
    y += f;
    z += f;
}

Vector3 Vector3::operator-(Vector3 v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

void Vector3::operator-=(Vector3 v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector3 Vector3::operator-(float f) const {
    return Vector3(x - f, y - f,  z - f);
}

void Vector3::operator-=(float f) {
    x -= f;
    y -= f;
    z -= f;
}

Vector3 Vector3::operator*(Vector3 v) const {
    return Vector3(x * v.x, y * v.y, z * v.z);
}

void Vector3::operator*=(Vector3 v) {
    x *= v.x;
    y *= v.y;
    z *= v.z;
}

Vector3 Vector3::operator*(float f) const {
    return Vector3(x * f, y * f, z * f);
}

void Vector3::operator*=(float f) {
    x *= f;
    y *= f;
    z *= f;
}

void Vector3::operator/=(Vector3 v) {
    (*this) *= v.invert();
}

Vector3 Vector3::operator/(float f) const {
    return (*this) * (1 / f);
}

void Vector3::operator/=(float f) {
    (*this) *= (1 / f);
}

Vector3 Vector3::cross(Vector3 v1, Vector3 v2) {
    return Vector3( v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}

float Vector3::angle(Vector3 v1, Vector3 v2) {
    return acos(dot(v1, v2) / (v1.length() * v2.length()));
}

float Vector3::distance(Vector3 v1, Vector3 v2) {
    return (v1 - v2).length();
}

Vector3 Vector3::reflect(Vector3 n) {
	Vector3 incident = *this; // we are the incident vector
	Vector3 normal   = n.normalize(); // make sure the normal is normalized
	
    return incident - normal * dot(incident, normal) * 2;
}

Vector3 Vector3::project(Vector3 v, Vector3 u) {
    //To-Do
    return v;
}

#ifdef AVMATH_GLM_INTEGRATION
    glm::vec3 Vector3::glm() const {
        return glm::vec3(x, y, z);
    }

    Vector3 Vector3::fromGLM(glm::vec3 vec) {
        return Vector3(vec.x, vec.y, vec.z);
    }
#endif
