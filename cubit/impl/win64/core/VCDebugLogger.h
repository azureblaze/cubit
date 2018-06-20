#pragma once
#include <cubit/core/Logger.h>
namespace cubit {
namespace impl {
class VCDebugLogger : public Logger {
 public:
  virtual void log(std::string_view line) override;
};
}  // namespace impl
}  // namespace cubit
