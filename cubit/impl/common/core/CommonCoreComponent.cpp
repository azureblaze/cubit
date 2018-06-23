#include "CommonCoreComponent.h"

#include <cubit/core/FrameUpdateMetrics.h>

namespace cubit {
namespace impl {
boost::di::injector<std::unique_ptr<cubit::impl::FrameRateGovernor>>
getCommonCoreInjector() {
  return boost::di::make_injector(
      getCommonConfigComponent(),
      getWin64OsComponent(),
      boost::di::bind<FrameRateGovernor>().to<SleepFutureGovernor>());
}
}  // namespace impl
}  // namespace cubit
