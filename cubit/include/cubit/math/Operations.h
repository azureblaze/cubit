#pragma once

#include "Constants.h"

namespace cubit {
template <class T>
T lerp(const T& a, const T& b, float beta) {
  return a * (1.0f - beta) + b * beta;
}

template <class T>
T clamp(const T& value, const T& min, const T& max) {
  if (value > max) {
    return max;
  }
  if (value < min) {
    return min;
  }
  return value;
}

inline float normalizeAngle(float rad) {
  rad = fmodf(rad, 2.0f * PI);
  if (rad < 0) {
    rad += 2.0 * PI;
  }
  return rad;
}
};  // namespace cubit
