#pragma once
#include "Matrix4.h"
#include "Quaternion.h"
#include "Vector3.h"

namespace cubit {
Vector3 Vector3::transformAsVector(const Matrix4& matrix) const {
  return (Vector3)(Vector4(*this, 0) * matrix);
}

Vector3 Vector3::transformAsPoint(const Matrix4& matrix) const {
  return (Vector3)(Vector4(*this, 1) * matrix);
}

Vector3 Vector3::rotate(const Quaternion& q) const {
  return (q * Quaternion(*this, 0) * q.inverse()).vector();
}
}  // namespace cubit
