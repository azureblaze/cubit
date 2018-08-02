#pragma once
#include "FrameRateGovernor.h"

#include <memory>

#include <fruit/fruit.h>

#include <cubit/Inject/Factory.h>
#include <cubit/os/Logger.h>
#include <cubit/os/SleepFuture.h>
#include <cubit/os/Timer.h>

namespace cubit {
class Config;
class FrameUpdateMetrics;
namespace impl {
class SleepFutureGovernor : public FrameRateGovernor {
 public:
  INJECT(SleepFutureGovernor(
      Config* config,
      Factory<SleepFuture> sleepFutureFactory,
      Factory<Timer> timerFactory,
      Factory<FrameUpdateMetrics> metrics));
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
