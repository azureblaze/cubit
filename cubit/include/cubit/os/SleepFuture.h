#pragma once

#include <cstdint>

namespace cubit {
class SleepFuture {
 public:
  virtual ~SleepFuture() = default;
  virtual void start(int64_t millis) = 0;
  virtual void get() = 0;
};
}  // namespace cubit
