#pragma once

#include <cubit/math/Math.h>

namespace cubit {
class Transform {
  Vector3 position;
  Quaternion rotation;
  Vector3 scale = Vector3(1, 1, 1);

 public:
  Transform& setPosition(const Vector3& position) {
    this->position = position;
    return *this;
  }

  const Vector3& getPosition() const { return position; }
  Vector3& getPosition() { return position; }

  Transform& setRotation(const Quaternion& rotation) {
    this->rotation = rotation;
    return *this;
  }

  const Quaternion& getRotation() const { return rotation; }
  Quaternion& getRotation() { return rotation; }

  Transform& setScale(const Vector3& scale) {
    this->scale = scale;
    return *this;
  }

  const Vector3& getScale() const { return scale; }
  Vector3& getScale() { return scale; }

  Matrix4 getTransform() {
    return Matrix4::scale(scale) * rotation.toMatrix() *
           Matrix4::translate(position);
  }
};
}  // namespace cubit
