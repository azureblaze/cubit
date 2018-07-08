#pragma once
#include <cmath>

namespace cubit {
class Matrix4;
class Quaternion;

class alignas(16) Vector2 {
  float u[2];

 public:
  Vector2() : u{} {};
  Vector2(float x, float y) : u{x, y} {}
  Vector2(const Vector2& other) { *this = other; }

  Vector2& operator=(const Vector2& other) {
    if (&other == this) {
      return *this;
    }
    u[0] = other[0];
    u[1] = other[1];
    return *this;
  }

  float* data() { return u; }
  const float* data() const { return u; }

  float& operator[](size_t index) { return u[index]; }
  const float& operator[](size_t index) const { return u[index]; }

  Vector2 operator+(const Vector2& v) const {
    return Vector2(u[0] + v[0], u[1] + v[1]);
  }

  Vector2 operator+() const { return *this; }

  Vector2 operator-(const Vector2& v) const {
    return Vector2(u[0] - v[0], u[1] - v[1]);
  }

  Vector2 operator-() const { return Vector2(-u[0], -u[1]); }

  Vector2 operator*(float k) const { return Vector2(u[0] * k, u[1] * k); }

  Vector2 operator/(float k) const { return Vector2(u[0] / k, u[1] / k); }

  Vector2& operator+=(const Vector2& v) { return *this = *this + v; }
  Vector2& operator-=(const Vector2& v) { return *this = *this - v; }
  Vector2& operator*=(float k) { return *this = *this * k; }
  Vector2& operator/=(float k) { return *this = *this / k; }

  float dot(const Vector2& v) const {
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
  }

  Vector2 cross(const Vector2& v) const {
    return Vector2(u[0] * v[1] - u[1] * v[0], u[1] * v[0] - u[0] * v[1]);
  }
  float length() const { return std::sqrtf(this->dot(*this)); }
  float length2() const { return this->dot(*this); }

  Vector2 normalize() const { return *this / length(); }
};  // namespace cubit

inline Vector2 operator*(float scale, const Vector2& v) { return v * scale; }
}  // namespace cubit
