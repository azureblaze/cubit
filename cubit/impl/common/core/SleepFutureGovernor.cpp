#include <cubit/core/FrameUpdateMetrics.h>
#include <cubit/core/config.h>
#include <deque>
#include "SleepFutureGovernor.h"
namespace cubit {
namespace impl {
SleepFutureGovernor::SleepFutureGovernor(
    std::shared_ptr<Config> config,
    const SleepFutureFactory& sleepFutureFactory,
    const TimerFactory& timerFactory,
    std::shared_ptr<Logger> logger,
    std::unique_ptr<FrameUpdateMetrics> metrics)
    : config(config),
      timer(timerFactory.create()),
      logger(logger),
      metrics(move(metrics)),
      nextFuture(sleepFutureFactory.create()),
      framePeriod(1.0f / config->get<float>("max_fps")) {}
void SleepFutureGovernor::start() { queueFuture(); }

static std::deque<float> runningAverage;

void SleepFutureGovernor::nextFrame() {
  float updateTime = timer->get();

  nextFuture->get();

  float frameTime = timer->get();
  targetTime -= frameTime;
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
