#pragma once

namespace cubit {
namespace impl {
class FrameRateGovernor {
 public:
  virtual ~FrameRateGovernor() = default;
  virtual void start() = 0;
  virtual void nextFrame() = 0;
};
}  // namespace impl
}  // namespace cubit
