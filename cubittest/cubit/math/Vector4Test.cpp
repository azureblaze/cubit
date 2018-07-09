#include "pch.h"

#include <cubit/math/math.h>

#include <cmath>
#include "MathTestUtill.h"

using namespace std;
using namespace cubit;

TEST(Vector4Test, defaultConstructor_zero) {
  Vector4 v;
  EXPECT_EQ(0, v[0]);
  EXPECT_EQ(0, v[1]);
  EXPECT_EQ(0, v[2]);
  EXPECT_EQ(0, v[3]);
}

TEST(Vector4Test, elementConstructor_elementsMatch) {
  Vector4 v(1, 2, 3, 4);
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
}

TEST(Vector4Test, copyConstructor_elementsMatch) {
  Vector4 copy(1, 2, 3, 4);
  Vector4 v(copy);
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
}

TEST(Vector4Test, vector3Constructor) {
  Vector4 v(Vector3(1, 2, 3), 4);
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
}

TEST(Vector4Test, assignmentOperator_elementsMatch) {
  Vector4 copy(1, 2, 3, 4);
  Vector4 v;
  v = copy;
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
  EXPECT_EQ(4, v[3]);
}

TEST(Vector4Test, data_returnFloatArray) {
  Vector4 v(1, 2, 3, 4);
  EXPECT_EQ(1, v.data()[0]);
  EXPECT_EQ(2, v.data()[1]);
  EXPECT_EQ(3, v.data()[2]);
  EXPECT_EQ(4, v.data()[3]);
}

TEST(Vector4Test, add) {
  Vector4 v = Vector4(1, 2, 3, 4) + Vector4(5, 6, 7, 8);
  EXPECT_FLOAT_EQ(6, v[0]);
  EXPECT_FLOAT_EQ(8, v[1]);
  EXPECT_FLOAT_EQ(10, v[2]);
  EXPECT_FLOAT_EQ(12, v[3]);
}

TEST(Vector4Test, unaryAdd) {
  Vector4 v = +Vector4(1, 2, 3, 4);
  EXPECT_FLOAT_EQ(1, v[0]);
  EXPECT_FLOAT_EQ(2, v[1]);
  EXPECT_FLOAT_EQ(3, v[2]);
  EXPECT_FLOAT_EQ(4, v[3]);
}

TEST(Vector4Test, subtract) {
  Vector4 v = Vector4(1, 2, 3, 4) - Vector4(2, 4, 6, 8);
  EXPECT_FLOAT_EQ(-1, v[0]);
  EXPECT_FLOAT_EQ(-2, v[1]);
  EXPECT_FLOAT_EQ(-3, v[2]);
  EXPECT_FLOAT_EQ(-4, v[3]);
}

TEST(Vector4Test, negate) {
  Vector4 v = -Vector4(1, 2, 3, 4);
  EXPECT_FLOAT_EQ(-1, v[0]);
  EXPECT_FLOAT_EQ(-2, v[1]);
  EXPECT_FLOAT_EQ(-3, v[2]);
  EXPECT_FLOAT_EQ(-4, v[3]);
}

TEST(Vector4Test, scale) {
  Vector4 v = Vector4(1, 2, 3, 4) * 2;
  EXPECT_FLOAT_EQ(2, v[0]);
  EXPECT_FLOAT_EQ(4, v[1]);
  EXPECT_FLOAT_EQ(6, v[2]);
  EXPECT_FLOAT_EQ(8, v[3]);
}

TEST(Vector4Test, floatScale) {
  Vector4 v = 2 * Vector4(1, 2, 3, 4);
  EXPECT_FLOAT_EQ(2, v[0]);
  EXPECT_FLOAT_EQ(4, v[1]);
  EXPECT_FLOAT_EQ(6, v[2]);
  EXPECT_FLOAT_EQ(8, v[3]);
}

TEST(Vector4Test, divide) {
  Vector4 v = Vector4(1, 2, 3, 4) / 2;
  EXPECT_FLOAT_EQ(0.5, v[0]);
  EXPECT_FLOAT_EQ(1, v[1]);
  EXPECT_FLOAT_EQ(1.5, v[2]);
  EXPECT_FLOAT_EQ(2, v[3]);
}

TEST(Vector4Test, addAssign) {
  Vector4 v(1, 2, 3, 4);
  v += Vector4(5, 6, 7, 8);
  EXPECT_FLOAT_EQ(6, v[0]);
  EXPECT_FLOAT_EQ(8, v[1]);
  EXPECT_FLOAT_EQ(10, v[2]);
  EXPECT_FLOAT_EQ(12, v[3]);
}

TEST(Vector4Test, subtractAssign) {
  Vector4 v(1, 2, 3, 4);
  v -= Vector4(2, 4, 6, 8);
  EXPECT_FLOAT_EQ(-1, v[0]);
  EXPECT_FLOAT_EQ(-2, v[1]);
  EXPECT_FLOAT_EQ(-3, v[2]);
  EXPECT_FLOAT_EQ(-4, v[3]);
}

TEST(Vector4Test, scaleAssign) {
  Vector4 v(1, 2, 3, 4);
  v *= 2;
  EXPECT_FLOAT_EQ(2, v[0]);
  EXPECT_FLOAT_EQ(4, v[1]);
  EXPECT_FLOAT_EQ(6, v[2]);
  EXPECT_FLOAT_EQ(8, v[3]);
}

TEST(Vector4Test, divideAssign) {
  Vector4 v(1, 2, 3, 4);
  v /= 2;
  EXPECT_FLOAT_EQ(0.5, v[0]);
  EXPECT_FLOAT_EQ(1, v[1]);
  EXPECT_FLOAT_EQ(1.5, v[2]);
  EXPECT_FLOAT_EQ(2, v[3]);
}

TEST(Vector4Test, dot) {
  Vector4 v1(1, 2, 3, 4);
  Vector4 v2(5, 6, 7, 8);

  EXPECT_FLOAT_EQ(1 * 5 + 2 * 6 + 3 * 7 + 4 * 8, v1.dot(v2));
}

TEST(Vector4Test, length) {
  Vector4 v(1, 2, 3, 4);

  EXPECT_FLOAT_EQ(sqrtf(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4), v.length());
}

TEST(Vector4Test, length2) {
  Vector4 v(1, 2, 3, 4);

  EXPECT_FLOAT_EQ(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4, v.length2());
}

TEST(Vector4Test, normalize) {
  Vector4 v(1, 2, 3, 4);
  Vector4 n = v.normalize();
  EXPECT_FLOAT_EQ(1 / v.length(), n[0]);
  EXPECT_FLOAT_EQ(2 / v.length(), n[1]);
  EXPECT_FLOAT_EQ(3 / v.length(), n[2]);
  EXPECT_FLOAT_EQ(4 / v.length(), n[3]);
}

TEST(Vector4Test, transform) {
  Vector4 v(5, 2, 2, 2);
  Matrix4 m =
      Matrix4({{0, .4f, 0, 0}, {2, 0, .5f, 0}, {5, 0, 0, .6f}, {2, 0, 0, 0}});

  Vector4 r = v * m;

  EXPECT_FLOAT_EQ(18, r[0]);
  EXPECT_FLOAT_EQ(2, r[1]);
  EXPECT_FLOAT_EQ(1, r[2]);
  EXPECT_FLOAT_EQ(1.2f, r[3]);
}

TEST(Vector4Test, convertToVector3) {
  Vector4 v4(1, 2, 3, 4);
  Vector3 v3 = (Vector3)v4;

  EXPECT_VECTOR3_EQ(Vector3(1, 2, 3), v3);
}
