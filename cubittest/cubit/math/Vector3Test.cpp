#include "pch.h"

#include <cubit/math/math.h>

#include "MathTestUtill.h"

using namespace cubit;

TEST(Vector3Test, defaultConstructor_allZero) {
  Vector3 v;

  EXPECT_FLOAT_EQ(0, v[0]);
  EXPECT_FLOAT_EQ(0, v[1]);
  EXPECT_FLOAT_EQ(0, v[2]);
}

TEST(Vector3Test, elementConstructor) {
  Vector3 v(1, 2, 3);

  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
  EXPECT_FLOAT_EQ(3, v[2]);
}

TEST(Vector3Test, copyConstructor) {
  Vector3 v(1, 2, 3);

  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
  EXPECT_FLOAT_EQ(3, v[2]);
}

TEST(Vector3Test, assignment) {
  Vector3 v;
  v = Vector3(1, 2, 3);

  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
  EXPECT_FLOAT_EQ(3, v[2]);
}

TEST(Vector3Test, add) {
  Vector3 v = Vector3(1, 2, 3) + Vector3(4, 5, 6);

  EXPECT_VECTOR3_EQ(Vector3(5, 7, 9), v);
}

TEST(Vector3Test, unaryAdd) {
  Vector3 v = +Vector3(4, 5, 6);

  EXPECT_VECTOR3_EQ(Vector3(4, 5, 6), v);
}

TEST(Vector3Test, subtract) {
  Vector3 v = Vector3(1, 2, 3) - Vector3(2, 4, 6);

  EXPECT_VECTOR3_EQ(Vector3(-1, -2, -3), v);
}

TEST(Vector3Test, negate) {
  Vector3 v = -Vector3(1, 2, 3);

  EXPECT_VECTOR3_EQ(Vector3(-1, -2, -3), v);
}

TEST(Vector3Test, scale) {
  Vector3 v = Vector3(1, 2, 3) * 2;

  EXPECT_VECTOR3_EQ(Vector3(2, 4, 6), v);
}

TEST(Vector3Test, floatScale) {
  Vector3 v = 2 * Vector3(1, 2, 3);

  EXPECT_VECTOR3_EQ(Vector3(2, 4, 6), v);
}

TEST(Vector3Test, divide) {
  Vector3 v = Vector3(1, 2, 3) / 2;

  EXPECT_VECTOR3_EQ(Vector3(0.5, 1, 1.5), v);
}

TEST(Vector3Test, addAssignment) {
  Vector3 v = Vector3(1, 2, 3);
  v += Vector3(4, 5, 6);

  EXPECT_VECTOR3_EQ(Vector3(5, 7, 9), v);
}

TEST(Vector3Test, subtractAssignment) {
  Vector3 v = Vector3(1, 2, 3);
  v -= Vector3(2, 4, 6);

  EXPECT_VECTOR3_EQ(Vector3(-1, -2, -3), v);
}

TEST(Vector3Test, scaleAssignment) {
  Vector3 v = Vector3(1, 2, 3);
  v *= 2;

  EXPECT_VECTOR3_EQ(Vector3(2, 4, 6), v);
}

TEST(Vector3Test, divideAssigment) {
  Vector3 v = Vector3(1, 2, 3);
  v /= 2;

  EXPECT_VECTOR3_EQ(Vector3(0.5, 1, 1.5), v);
}

TEST(Vector3Test, dot) {
  float v = Vector3(1, 2, 3).dot(Vector3(4, 5, 6));

  EXPECT_FLOAT_EQ(32, v);
}

TEST(Vector3Test, cross) {
  Vector3 v = Vector3(1, 2, 3).cross(Vector3(4, 5, 6));

  EXPECT_VECTOR3_EQ(Vector3(-3, 6, -3), v);
}

TEST(Vector3Test, length) {
  float v = Vector3(1, 2, 3).length();

  EXPECT_FLOAT_EQ(sqrtf(14), v);
}

TEST(Vector3Test, length2) {
  float v = Vector3(1, 2, 3).length2();

  EXPECT_FLOAT_EQ(14, v);
}

TEST(Vector3Test, normalize) {
  Vector3 v = Vector3(1, 2, 3).normalize();

  EXPECT_VECTOR3_EQ(Vector3(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)), v);
}

TEST(Vector3Test, transformAsVector) {
  Vector3 v = Vector3(1, 2, 3).transformAsVector(
      Matrix4::rotateX(PI_2) * Matrix4::translate(Vector3(1, 2, 3)));

  EXPECT_VECTOR3_EQ(Vector3(1, -3, 2), v);
}

TEST(Vector3Test, transformAsPoint) {
  Vector3 v = Vector3(1, 2, 3).transformAsPoint(
      Matrix4::rotateX(PI_2) * Matrix4::translate(Vector3(1, 2, 3)));

  EXPECT_VECTOR3_EQ(Vector3(2, -1, 5), v);
}

TEST(Vector3Test, rotate) {
  Vector3 v =
      Vector3(1, 2, 3).rotate(Quaternion::fromAxis(Vector3(1, 0, 0), PI_2));

  EXPECT_VECTOR3_EQ(Vector3(1, -3, 2), v);
}
