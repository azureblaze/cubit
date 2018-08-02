#include <iomanip>

#include <cubit/config/Config.h>
#include <cubit/core/FrameUpdateMetrics.h>
#include <cubit/os/Logger.h>

using namespace std;
namespace cubit {
FrameUpdateMetrics ::FrameUpdateMetrics(Config* config, Logger* logger)
    : config(*config),
      logger(*logger),
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
  ostringstream ss;
  ss << "UPS: " << fixed << setw(5) << setprecision(1)
     << (float)period / frameSum << " Load: " << fixed << setw(5)
     << setprecision(2) << (updateSum / frameSum * 100.f) << "%\n";
  logger.log(ss.str());
}

void FrameUpdateMetrics::addFrameData(const Metric& metric) {
  metrics.push_back(metric);
  if (metrics.size() == period) {
    logMetrics();
    metrics.clear();
  }
}
}  // namespace cubit
