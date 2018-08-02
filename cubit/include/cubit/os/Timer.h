#pragma once

namespace cubit {
class Timer {
 public:
  virtual ~Timer() = default;
  virtual void start() = 0;
  virtual float get() = 0;
};
}  // namespace cubit
