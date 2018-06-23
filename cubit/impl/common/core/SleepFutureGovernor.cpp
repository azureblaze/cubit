#include "SleepFutureGovernor.h"

#include <deque>

#include <cubit/config/config.h>
#include <cubit/core/FrameUpdateMetrics.h>

namespace cubit {
namespace impl {
SleepFutureGovernor::SleepFutureGovernor(
    Config& config,
    const SleepFutureFactory& sleepFutureFactory,
    const TimerFactory& timerFactory,
    std::unique_ptr<FrameUpdateMetrics> metrics)
    : config(config),
      timer(timerFactory.create()),
      metrics(move(metrics)),
      nextFuture(sleepFutureFactory.create()),
      framePeriod(1.0f / config.get<float>("max_fps")) {}
void SleepFutureGovernor::start() { queueFuture(); }

static std::deque<float> runningAverage;

void SleepFutureGovernor::nextFrame() {
  float updateTime = timer->get();

  nextFuture->get();

  float frameTime = timer->get();
  targetTime -= frameTime;

  // clamp catchup from a slow frame to 1 frame.
  if (targetTime < -framePeriod) {
    targetTime = -framePeriod;
  }

  metrics->addFrameData({updateTime, frameTime});
  queueFuture();
}

void SleepFutureGovernor::queueFuture() {
  timer->start();
  targetTime += framePeriod;
  nextFuture->start((uint64_t)(targetTime * 1000.f));
}
}  // namespace impl
}  // namespace cubit
