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
