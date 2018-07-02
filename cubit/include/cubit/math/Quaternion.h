#pragma once

#include <cmath>

#include "Matrix4.h"
#include "Vector3.h"

#include "Operations.h"

namespace cubit {
class Quaternion {
  Vector3 v;
  float s;

 public:
  Quaternion(const Vector3& v, float s) : v(v), s(s) {}

  static Quaternion fromAxis(const Vector3& axis, float theta) {
    return Quaternion(
        axis.normalize() * std::sinf(theta / 2.0f), std::cosf(theta / 2.0f));
  }

  Quaternion(const Quaternion& q) { *this = q; }

  Quaternion& operator=(const Quaternion& q) {
    v = q.v;
    s = q.s;
    return *this;
  }

  Vector3& vector() { return v; }
  const Vector3& vector() const { return v; }

  float& scaler() { return s; }
  float scaler() const { return s; }

  Quaternion inverse() const { return Quaternion(-v, s); }

  float length2() const { return v.length2() + s * s; }

  float length() const { return std::sqrtf(length2()); }

  Quaternion normalize() const {
    float l = length();
    return Quaternion(v / l, s / l);
  }

  Quaternion operator*(const Quaternion& q) const {
    const Quaternion& p = *this;
    return Quaternion(
        p.s * q.v + q.s * p.v + p.v.cross(q.v), p.s * q.s - p.v.dot(q.v));
  }

  Matrix4 toMatrix() const {
    const float& x = v[0];
    const float& y = v[1];
    const float& z = v[2];
    const float& w = s;
    // clang-format off
    return Matrix4{
      {1 - 2*y*y - 2*z*z, 2*x*y + 2*z*w,     2*x*z - 2*y*w,    0},
      {2*x*y - 2*z*w,     1 - 2*x*x - 2*z*z, 2*y*z + 2*x*w,    0},
      {2*x*z + 2*y*w,     2*y*z - 2*x*w,     1 - 2*x*x -2*y*y, 0},
      {0,                 0,                 0,               1}};
    // clang-format on
  }
  static Quaternion slerp(const Quaternion& a, const Quaternion& b) {}
};

inline Quaternion lerp(const Quaternion& a, const Quaternion& b, float beta) {
  return Quaternion(
             lerp<Vector3>(a.vector(), b.vector(), beta),
             lerp<float>(a.scaler(), b.scaler(), beta))
      .normalize();
}

inline Quaternion slerp(const Quaternion& a, const Quaternion& b, float beta) {
  float theta =
      std::acosf(a.vector().dot(b.vector()) + a.scaler() * b.scaler());
  float wp = sinf((1 - beta) * theta) / sinf(theta);
  float wq = sinf(beta * theta) / sin(theta);

  return Quaternion(
      a.vector() * wp + b.vector() * wq, a.scaler() * wp + b.scaler() * wq);
}

}  // namespace cubit
