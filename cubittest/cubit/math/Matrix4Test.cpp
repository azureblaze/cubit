#include "pch.h"

#include <cubit/math/math.h>

#include "MathTestUtill.h"

using namespace cubit;

const static Matrix4 TEST =
    Matrix4{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

const static Matrix4 TEST2 = Matrix4{{17, 18, 19, 20},
                                     {21, 22, 23, 24},
                                     {25, 26, 27, 28},
                                     {29, 30, 31, 32}};

TEST(Matrix4Test, defaultConstructor_allZero) {
  Matrix4 m;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_FLOAT_EQ(0, m[i][j]);
    }
  }
}

TEST(Matrix4Test, elementsConstructor_equalsElement) {
  Matrix4 m{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};

  int k = 1;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_FLOAT_EQ(k, m[i][j]);
      k++;
    }
  }
}

TEST(Matrix4Test, copyConstructor_equals) {
  Matrix4 m(TEST);

  EXPECT_MATRIX4_EQ(TEST, m);
}

TEST(Matrix4Test, assignment_equals) {
  Matrix4 m;
  m = TEST;

  EXPECT_MATRIX4_EQ(TEST, m);
}

TEST(Matrix4Test, scale) {
  Matrix4 m = TEST * 2;

  EXPECT_MATRIX4_EQ(
      {{2, 4, 6, 8}, {10, 12, 14, 16}, {18, 20, 22, 24}, {26, 28, 30, 32}}, m);
}

TEST(Matrix4Test, scaleFloatMatrix) {
  Matrix4 m = 2 * TEST;

  EXPECT_MATRIX4_EQ(
      {{2, 4, 6, 8}, {10, 12, 14, 16}, {18, 20, 22, 24}, {26, 28, 30, 32}}, m);
}

TEST(Matrix4Test, multiply) {
  Matrix4 m = TEST * TEST2;

  EXPECT_MATRIX4_EQ(
      {{250, 260, 270, 280},
       {618, 644, 670, 696},
       {986, 1028, 1070, 1112},
       {1354, 1412, 1470, 1528}},
      m);
}

TEST(Matrix4Test, transpose) {
  Matrix4 m = TEST.transpose();

  EXPECT_MATRIX4_EQ(
      {{1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15}, {4, 8, 12, 16}}, m);
}

TEST(Matrix4Test, identity) {
  Matrix4 m = TEST * Matrix4::identity();

  EXPECT_MATRIX4_EQ(TEST, m);
}

TEST(Matrix4Test, translate) {
  Matrix4 m = Matrix4::translate(Vector3(1, 2, 3));
  Vector3 v = Vector3(4, 5, 6).transformAsPoint(m);

  EXPECT_VECTOR3_EQ(Vector3(5, 7, 9), v);
}

TEST(Matrix4Test, rotateX) {
  Matrix4 m = Matrix4::rotateX(PI_2);
  Vector3 v = Vector3(0, 1, 0).transformAsPoint(m);
  EXPECT_VECTOR3_EQ(Vector3(0, 0, 1), v);
}

TEST(Matrix4Test, rotateY) {
  Matrix4 m = Matrix4::rotateY(PI_2);
  Vector3 v = Vector3(1, 0, 0).transformAsPoint(m);
  EXPECT_VECTOR3_EQ(Vector3(0, 0, -1), v);
}

TEST(Matrix4Test, rotateZ) {
  Matrix4 m = Matrix4::rotateZ(PI_2);
  Vector3 v = Vector3(0, 1, 0).transformAsPoint(m);
  EXPECT_VECTOR3_EQ(Vector3(-1, 0, 0), v);
}

TEST(Matrix4Test, scaleTransform) {
  Matrix4 m = Matrix4::scale(Vector3(2, 3, 4));
  Vector3 v = Vector3(1, 2, 3).transformAsPoint(m);
  EXPECT_VECTOR3_EQ(Vector3(2, 6, 12), v);
}

TEST(Matrix4Test, lookAt) {
  Matrix4 m =
      Matrix4::lookAt(Vector3(1, 2, 3), Vector3(2, 4, 6), Vector3(0, 1, 0));
  Vector3 v = Vector3(1, 0, 0).transformAsPoint(m);
  EXPECT_VECTOR3_EQ(Vector3(1, 2, 3) + Vector3(1, 2, 3).normalize(), v);
}
