#include "pch.h"

#include <cubit/math/Math.h>

#include "MathTestUtill.h"

using namespace cubit;

TEST(OperationsTest, lerpFloat) {
  EXPECT_FLOAT_EQ(1.25f, lerp<float>(1, 2, 0.25));
}

TEST(OperationsTest, lerpVector3) {
  EXPECT_VECTOR3_EQ(
      Vector3(1.25, 2.25, 3.25),
      lerp(Vector3(1, 2, 3), Vector3(2, 3, 4), 0.25));
}

TEST(OperationsTest, clamp_less) { EXPECT_EQ(1, clamp(0, 1, 2)); }
TEST(OperationsTest, clamp_more) { EXPECT_EQ(2, clamp(3, 1, 2)); }
TEST(OperationsTest, clamp_inRange) { EXPECT_EQ(2, clamp(2, 1, 3)); }

TEST(OperationsTest, normalizeAngle_less) {
  EXPECT_FLOAT_EQ(2 * PI - PI_2, normalizeAngle(-(6 * PI + PI_2)));
}
TEST(OperationsTest, normalizeAngle_more) {
  EXPECT_FLOAT_EQ(PI_2, normalizeAngle(6 * PI + PI_2));
}
TEST(OperationsTest, normalizeAngle_inRange) {
  EXPECT_FLOAT_EQ(PI_2, normalizeAngle(PI_2));
}

TEST(OperationsTest, normalizeAngle_zero) {
  EXPECT_FLOAT_EQ(0, normalizeAngle(0));
}

TEST(OperationsTest, normalizeAngle_2Pi) {
  EXPECT_FLOAT_EQ(0, normalizeAngle(2 * PI));
}
