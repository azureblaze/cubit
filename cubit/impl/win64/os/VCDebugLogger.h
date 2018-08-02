#pragma once
#include <cubit/os/Logger.h>

#include <fruit/fruit.h>

namespace cubit {
namespace impl {
class VCDebugLogger : public Logger {
 public:
  INJECT(VCDebugLogger()) = default;
  virtual void log(std::string_view line) override;
};
}  // namespace impl
}  // namespace cubit
