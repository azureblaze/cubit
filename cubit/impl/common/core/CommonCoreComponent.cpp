#include "CommonCoreComponent.h"

#include <cubit/config/config.h>
#include <cubit/core/FrameUpdateMetrics.h>

using namespace std;

namespace cubit {
namespace impl {
CommonCoreComponent getCommonCoreInjector() {
  return fruit::createComponent()
      .bind<FrameRateGovernor, SleepFutureGovernor>();
}
}  // namespace impl
}  // namespace cubit
