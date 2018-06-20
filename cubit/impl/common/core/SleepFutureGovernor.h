#pragma once
#include <cubit/core/Logger.h>
#include <cubit/core/SleepFuture.h>
#include <cubit/core/Timer.h>
#include <memory>
#include "FrameRateGovernor.h"

namespace cubit {
class Config;
class FrameUpdateMetrics;
namespace impl {
class SleepFutureGovernor : public FrameRateGovernor {
 public:
  SleepFutureGovernor(
      std::shared_ptr<Config> config,
      const SleepFutureFactory& sleepFutureFactory,
      const TimerFactory& timerFactory,
      std::shared_ptr<Logger> logger,
      std::unique_ptr<FrameUpdateMetrics> metrics);
  virtual void start();
  virtual void nextFrame();

 private:
  std::shared_ptr<Config> config;
  const float framePeriod;

  std::unique_ptr<SleepFuture> nextFuture;
  std::unique_ptr<Timer> timer;
  std::shared_ptr<Logger> logger;
  std::unique_ptr<FrameUpdateMetrics> metrics;
  float targetTime = 0.0f;

  void queueFuture();
};
}  // namespace impl
}  // namespace cubit
