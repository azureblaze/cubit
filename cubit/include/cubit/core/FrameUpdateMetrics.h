#pragma once
#include <memory>
#include <vector>

#include <fruit/fruit.h>

namespace cubit {
class Config;
class Logger;
class FrameUpdateMetrics {
 public:
  struct Metric {
    float updateTime;
    float frameTime;
  };
  INJECT(FrameUpdateMetrics(Config* config, Logger* logger));

  void addFrameData(const Metric& metric);

 private:
  Config& config;
  Logger& logger;
  std::vector<Metric> metrics;

  int period;

  void logMetrics();
};
}  // namespace cubit
