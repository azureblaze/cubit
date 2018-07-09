#include "pch.h"

#include <cubit/math/math.h>

#include "MathTestUtill.h"

using namespace cubit;

TEST(Vector2Test, defaultConstructor_allZero) {
  Vector2 v;

  EXPECT_FLOAT_EQ(0, v[0]);
  EXPECT_FLOAT_EQ(0, v[1]);
}

TEST(Vector2Test, elementConstructor) {
  Vector2 v(1, 2);

  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
}

TEST(Vector2Test, copyConstructor) {
  Vector2 v(1, 2);

  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
}

TEST(Vector2Test, assignment) {
  Vector2 v;
  v = Vector2(1, 2);

  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
}

TEST(Vector2Test, add) {
  Vector2 v = Vector2(1, 2) + Vector2(4, 5);

  EXPECT_VECTOR2_EQ(Vector2(5, 7), v);
}

TEST(Vector2Test, unaryAdd) {
  Vector2 v = +Vector2(4, 5);

  EXPECT_VECTOR2_EQ(Vector2(4, 5), v);
}

TEST(Vector2Test, subtract) {
  Vector2 v = Vector2(1, 2) - Vector2(2, 4);

  EXPECT_VECTOR2_EQ(Vector2(-1, -2), v);
}

TEST(Vector2Test, negate) {
  Vector2 v = -Vector2(1, 2);

  EXPECT_VECTOR2_EQ(Vector2(-1, -2), v);
}

TEST(Vector2Test, scale) {
  Vector2 v = Vector2(1, 2) * 2;

  EXPECT_VECTOR2_EQ(Vector2(2, 4), v);
}

TEST(Vector2Test, floatScale) {
  Vector2 v = 2 * Vector2(1, 2);

  EXPECT_VECTOR2_EQ(Vector2(2, 4), v);
}

TEST(Vector2Test, divide) {
  Vector2 v = Vector2(1, 2) / 2;

  EXPECT_VECTOR2_EQ(Vector2(0.5, 1), v);
}

TEST(Vector2Test, addAssignment) {
  Vector2 v = Vector2(1, 2);
  v += Vector2(4, 5);

  EXPECT_VECTOR2_EQ(Vector2(5, 7), v);
}

TEST(Vector2Test, subtractAssignment) {
  Vector2 v = Vector2(1, 2);
  v -= Vector2(2, 4);

  EXPECT_VECTOR2_EQ(Vector2(-1, -2), v);
}

TEST(Vector2Test, scaleAssignment) {
  Vector2 v = Vector2(1, 2);
  v *= 2;

  EXPECT_VECTOR2_EQ(Vector2(2, 4), v);
}

TEST(Vector2Test, divideAssigment) {
  Vector2 v = Vector2(1, 2);
  v /= 2;

  EXPECT_VECTOR2_EQ(Vector2(0.5, 1), v);
}

TEST(Vector2Test, dot) {
  float v = Vector2(1, 2).dot(Vector2(4, 5));

  EXPECT_FLOAT_EQ(14, v);
}

TEST(Vector2Test, cross) {
  float f = Vector2(1, 2).cross(Vector2(4, 5));

  EXPECT_FLOAT_EQ(-3, f);
}

TEST(Vector2Test, length) {
  float v = Vector2(1, 2).length();

  EXPECT_FLOAT_EQ(sqrtf(5), v);
}

TEST(Vector2Test, length2) {
  float v = Vector2(1, 2).length2();

  EXPECT_FLOAT_EQ(5, v);
}

TEST(Vector2Test, normalize) {
  Vector2 v = Vector2(1, 2).normalize();

  EXPECT_VECTOR2_EQ(Vector2(1 / sqrtf(5), 2 / sqrtf(5)), v);
}

TEST(Vector2Test, angle) {
  float f = Vector2(1, -1).angle();

  EXPECT_FLOAT_EQ(atan2(-1, 1), f);
}

TEST(Vector2Test, rotate) {
  Vector2 v = Vector2(1, 2).rotate(PI_2);

  EXPECT_VECTOR2_EQ(Vector2(-2, 1), v);
}
