#include <cubit/core/Config.h>
#include <cubit/core/FrameUpdateMetrics.h>
#include <cubit/core/Logger.h>

namespace cubit {
FrameUpdateMetrics ::FrameUpdateMetrics(
    std::shared_ptr<Config> config,
    std::shared_ptr<Logger> logger)
    : config(config),
      logger(logger),
      period(config->get<int>("frame_update_metrics_period")) {
  metrics.reserve(period);
}

void FrameUpdateMetrics::logMetrics() {
  float updateSum = 0;
  float frameSum = 0;
  for (const auto& metric : metrics) {
    updateSum += metric.updateTime;
    frameSum += metric.frameTime;
  }
  logger->stream() << "UPS: " << (float)period / frameSum
                   << " Load: " << (updateSum / frameSum * 100.f) << "%\n";
}

void FrameUpdateMetrics::addFrameData(const Metric& metric) {
  metrics.push_back(metric);
  if (metrics.size() == period) {
    logMetrics();
    metrics.clear();
  }
}
}  // namespace cubit
