#pragma once
#include "FrameRateGovernor.h"

#include <memory>

#include <cubit/os/Logger.h>
#include <cubit/os/SleepFuture.h>
#include <cubit/os/Timer.h>

namespace cubit {
class Config;
class FrameUpdateMetrics;
namespace impl {
class SleepFutureGovernor : public FrameRateGovernor {
 public:
  SleepFutureGovernor(
      Config& config,
      const SleepFutureFactory& sleepFutureFactory,
      const TimerFactory& timerFactory,
      std::unique_ptr<FrameUpdateMetrics> metrics);
  virtual void start();
  virtual void nextFrame();

 private:
  Config& config;
  const float framePeriod;

  std::unique_ptr<SleepFuture> nextFuture;
  std::unique_ptr<Timer> timer;
  std::unique_ptr<FrameUpdateMetrics> metrics;
  float targetTime = 0.0f;

  void queueFuture();
};
}  // namespace impl
}  // namespace cubit
