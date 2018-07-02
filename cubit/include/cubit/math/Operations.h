#pragma once

namespace cubit {
template <class T>
T lerp(const T& a, const T& b, float beta) {
  return a * (1.0f - beta) + b * beta;
}
};  // namespace cubit
