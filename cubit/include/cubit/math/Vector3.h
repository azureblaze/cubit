#pragma once
#include <cmath>

namespace cubit {
class Vector3;
class Matrix4;

class alignas(16) Vector3 {
  float u[3];

 public:
  Vector3() : u{} {};
  Vector3(float x, float y, float z) : u{x, y, z} {}
  Vector3(const Vector3& other) { *this = other; }

  Vector3& operator=(const Vector3& other) {
    if (&other == this) {
      return *this;
    }
    u[0] = other[0];
    u[1] = other[1];
    u[2] = other[2];
  }

  float* data() { return u; }
  const float* data() const { return u; }

  float& operator[](size_t index) { return u[index]; }
  const float& operator[](size_t index) const { return u[index]; }

  Vector3 operator+(const Vector3& v) const {
    return Vector3(u[0] + v[0], u[1] + v[1], u[2] + v[2]);
  }

  Vector3 operator+() const { return *this; }

  Vector3 operator-(const Vector3& v) const {
    return Vector3(u[0] - v[0], u[1] - v[1], u[2] - v[2]);
  }

  Vector3 operator-() const { return Vector3(-u[0], -u[1], -u[2]); }

  Vector3 operator*(float k) const {
    return Vector3(u[0] * k, u[1] * k, u[2] * k);
  }

  Vector3 operator/(float k) const {
    return Vector3(u[0] / k, u[1] / k, u[2] / k);
  }

  Vector3& operator+=(const Vector3& v) { return *this = *this + v; }
  Vector3& operator-=(const Vector3& v) { return *this = *this - v; }
  Vector3& operator*=(float k) { return *this = *this * k; }
  Vector3& operator/=(float k) { return *this = *this / k; }

  float dot(const Vector3& v) const {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
  }

  Vector3 cross(const Vector3& v) const {
    return Vector3(
        u[1] * v[2] - u[2] * v[1],
        u[0] * v[2] - u[2] * v[0],
        u[0] * v[1] - u[1] * v[0]);
  }
  float length() const { return std::sqrtf(this->dot(*this)); }
  float length2() const { return this->dot(*this); }

  Vector3 normalize() const { return *this / length(); }

  inline Vector3 transformAsVector(const Matrix4& matrix) const;
  inline Vector3 transformAsPoint(const Matrix4& matrix) const;
};  // namespace cubit

inline Vector3 operator*(float scale, const Vector3& v) { return v * scale; }
}  // namespace cubit
