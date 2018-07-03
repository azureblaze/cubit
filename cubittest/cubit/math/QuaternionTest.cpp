#include "pch.h"

#include <cubit/math/Math.h>

#include "MathTestUtill.h"

using namespace cubit;

TEST(QuaternionTest, constructor) {
  Quaternion q(Vector3(1, 2, 3), 4);
  EXPECT_QUATERNION_EQ(Quaternion(Vector3(1, 2, 3), 4), q);
}

TEST(QuaternionTest, copyConstructor) {
  Quaternion p = Quaternion(Vector3(1, 2, 3), 4);
  Quaternion q(p);
  EXPECT_QUATERNION_EQ(Quaternion(Vector3(1, 2, 3), 4), q);
}

TEST(QuaternionTest, fromAxis) {
  Quaternion q = Quaternion::fromAxis(Vector3(3, 0, 0), PI_2);

  EXPECT_QUATERNION_EQ(
      Quaternion(Vector3(sinf(PI / 4), 0, 0), cosf(PI / 4)), q);
}

TEST(QuaternionTest, assignment) {
  Quaternion p = Quaternion(Vector3(1, 2, 3), 4);
  Quaternion q(Vector3(0, 0, 0), 0);
  q = p;
  EXPECT_QUATERNION_EQ(Quaternion(Vector3(1, 2, 3), 4), q);
}

TEST(QuaternionTest, inverse) {
  Quaternion q = Quaternion(Vector3(1, 2, 3), 4).inverse();
  // test for conjugate instead.
  EXPECT_QUATERNION_EQ(Quaternion(-Vector3(1, 2, 3), 4), q);
}

TEST(QuaternionTest, multipy) {
  Quaternion q = Quaternion::fromAxis(Vector3(0, 1, 0), PI_2) *
                 Quaternion::fromAxis(Vector3(1, 0, 0), PI_2);

  Vector3 v = Vector3(1, 0, -1).rotate(q);
  EXPECT_VECTOR3_EQ(Vector3(0, 1, -1), v);
}

TEST(QuaternionTest, toMatrix) {
  Matrix4 m = Quaternion::fromAxis(Vector3(1, 0, 0), 4).toMatrix();

  EXPECT_MATRIX4_EQ(Matrix4::rotateX(4), m);
}

TEST(QuaternionTest, lerp) {
  Quaternion q = lerp(
      Quaternion::fromAxis(Vector3(1, 0, 0), 0),
      Quaternion::fromAxis(Vector3(1, 0, 0), PI),
      0.5f);

  EXPECT_QUATERNION_EQ(Quaternion::fromAxis(Vector3(1, 0, 0), PI / 2), q);
}

TEST(QuaternionTest, slerp) {
  Quaternion q = slerp(
      Quaternion::fromAxis(Vector3(1, 0, 0), 0),
      Quaternion::fromAxis(Vector3(1, 0, 0), PI),
      0.25f);

  EXPECT_QUATERNION_EQ(Quaternion::fromAxis(Vector3(1, 0, 0), PI / 4), q);
}

TEST(QuaternionTest, fromRotationMatrix) {
  Quaternion q = Quaternion::fromRotationMatrix(Matrix4::rotateX(1));

  EXPECT_MATRIX4_EQ(Matrix4::rotateX(1), q.toMatrix());
}

TEST(QuaternionTest, lookAt) {
  Quaternion q = Quaternion::lookAt(Vector3(1, 2, 3), Vector3(0, 1, 0));

  Vector3 v = Vector3(1, 0, 0).rotate(q);
  EXPECT_VECTOR3_EQ(Vector3(1, 2, 3).normalize(), v);
}
