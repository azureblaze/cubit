#pragma once

#include "Transform.h"

namespace cubit {

class Camera {
  Transform transform;

 public:
  Camera() {}

  Transform& getTransform() { return transform; }
  const Transform& getTransform() const { return transform; }

  Matrix4 getViewProjection(float width, float height, float near, float far)
      const {
    // inv (scale * rotate * translate)
    Matrix4 view =
        Matrix4::translate(-transform.getPosition()) *
        // projection points to z+, rotate so it points to x+
        (transform.getRotation() * Quaternion::fromAxis(Vector3(0, 1, 0), PI_2))
            .inverse()
            .toMatrix() *
        Matrix4::scale(Vector3(
            1 / transform.getScale()[0],
            1 / transform.getScale()[1],
            1 / transform.getScale()[2]));

    Matrix4 projection =
        Matrix4::perspectiveProjection(width, height, near, far);

    return view * projection;
  }
};

}  // namespace cubit
