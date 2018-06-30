#pragma once
#include "Matrix4.h"
#include "Vector3.h"

namespace cubit {
Vector3 Vector3::transformAsVector(const Matrix4& matrix) const {
  return (Vector3)(Vector4(*this, 0) * matrix);
}

Vector3 Vector3::transformAsPoint(const Matrix4& matrix) const {
  return (Vector3)(Vector4(*this, 1) * matrix);
}
}  // namespace cubit
