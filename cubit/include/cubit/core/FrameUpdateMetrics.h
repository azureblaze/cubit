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
  FrameUpdateMetrics(
      std::shared_ptr<Config> config,
      std::shared_ptr<Logger> logger);

  void addFrameData(const Metric& metric);

 private:
  std::shared_ptr<Config> config;
  std::shared_ptr<Logger> logger;
  std::vector<Metric> metrics;

  int period;

  void logMetrics();
};
}  // namespace cubit
