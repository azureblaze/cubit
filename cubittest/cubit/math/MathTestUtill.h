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
  for (int i = 0; i < 4; i++) {
    EXPECT_NEAR(expected[i], result[i], FLOAT_COMPARISON_PERCISION);
  }
}

inline void EXPECT_VECTOR3_EQ(const Vector3& expected, const Vector3& result) {
  for (int i = 0; i < 3; i++) {
    EXPECT_NEAR(expected[i], result[i], FLOAT_COMPARISON_PERCISION);
  }
}
}  // namespace cubit
