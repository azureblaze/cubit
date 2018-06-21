#pragma once
#include <memory>
#include <vector>
namespace cubit {
class Config;
class Logger;
class FrameUpdateMetrics {
 public:
  struct Metric {
    float updateTime;
    float frameTime;
  };
  FrameUpdateMetrics(Config& config, Logger& logger);

  void addFrameData(const Metric& metric);

 private:
  Config& config;
  Logger& logger;
  std::vector<Metric> metrics;

  int period;

  void logMetrics();
};
}  // namespace cubit
