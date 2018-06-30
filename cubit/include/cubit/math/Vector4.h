#pragma once
#include <cmath>
#include "Vector3.h"
namespace cubit {
class Matrix4;

class alignas(16) Vector4 {
  float u[4];

 public:
  Vector4() : u{} {};
  Vector4(float x, float y, float z, float w) : u{x, y, z, w} {}
  Vector4(const Vector4& other) { *this = other; }
  Vector4(const Vector3& other, float w)
      : Vector4(other[0], other[1], other[2], w) {}

  explicit operator Vector3() const { return Vector3(u[0], u[1], u[2]); }

  Vector4& operator=(const Vector4& v) {
    if (&v == this) {
      return *this;
    }
    u[0] = v[0];
    u[1] = v[1];
    u[2] = v[2];
    u[3] = v[3];
  }

  float* data() { return u; }
  const float* data() const { return u; }

  float& operator[](size_t index) { return u[index]; }
  const float& operator[](size_t index) const { return u[index]; }

  Vector4 operator+(const Vector4& v) const {
    return Vector4(u[0] + v[0], u[1] + v[1], u[2] + v[2], u[3] + v[3]);
  }

  Vector4 operator+() const { return *this; }

  Vector4 operator-(const Vector4& v) const {
    return Vector4(u[0] - v[0], u[1] - v[1], u[2] - v[2], u[3] - v[3]);
  }

  Vector4 operator-() const { return Vector4(-u[0], -u[1], -u[2], -u[3]); }

  Vector4 operator*(float k) const {
    return Vector4(u[0] * k, u[1] * k, u[2] * k, u[3] * k);
  }

  inline Vector4 operator*(const Matrix4& transform);

  Vector4 operator/(float k) const {
    return Vector4(u[0] / k, u[1] / k, u[2] / k, u[3] / k);
  }

  Vector4& operator+=(const Vector4& v) { return *this = *this + v; }
  Vector4& operator-=(const Vector4& v) { return *this = *this - v; }
  Vector4& operator*=(float k) { return *this = *this * k; }
  Vector4& operator/=(float k) { return *this = *this / k; }

  float dot(const Vector4& k) const {
    return u[0] * k[0] + u[1] * k[1] + u[2] * k[2] + u[3] * k[3];
  }

  float length() const { return std::sqrtf(this->dot(*this)); }
  float length2() const { return this->dot(*this); }

  Vector4 normalize() const { return *this / length(); }
};  // namespace cubit

inline Vector4 operator*(float scale, const Vector4& v) { return v * scale; }
}  // namespace cubit
