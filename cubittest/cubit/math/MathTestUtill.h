#pragma once
#include <cubit/math/Math.h>

namespace cubit {

constexpr float FLOAT_COMPARISON_PERCISION = 1e-6;

inline void EXPECT_MATRIX4_EQ(const Matrix4& expected, const Matrix4& result) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_NEAR(expected[i][j], result[i][j], FLOAT_COMPARISON_PERCISION);
    }
  }
}

inline void EXPECT_VECTOR4_EQ(const Vector4& expected, const Vector4& result) {
  EXPECT_NEAR(expected[0], result[0], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(expected[1], result[1], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(expected[2], result[2], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(expected[3], result[3], FLOAT_COMPARISON_PERCISION);
}

inline void EXPECT_VECTOR3_EQ(const Vector3& expected, const Vector3& result) {
  EXPECT_NEAR(expected[0], result[0], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(expected[1], result[1], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(expected[2], result[2], FLOAT_COMPARISON_PERCISION);
}

inline void EXPECT_QUATERNION_EQ(
    const Quaternion& expected,
    const Quaternion& result) {
  EXPECT_NEAR(
      expected.vector()[0], result.vector()[0], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(
      expected.vector()[1], result.vector()[1], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(
      expected.vector()[2], result.vector()[2], FLOAT_COMPARISON_PERCISION);
  EXPECT_NEAR(expected.scaler(), result.scaler(), FLOAT_COMPARISON_PERCISION);
}
}  // namespace cubit
