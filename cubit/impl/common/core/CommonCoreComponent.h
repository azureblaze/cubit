#pragma once
#include <boost/di.hpp>
#include <memory>
#include "ConstMapConfig.h"
#include "FrameRateGovernor.h"
#include "SleepFutureGovernor.h"
namespace cubit {
class Config;
namespace impl {
class ConstMapConfig;
inline auto getCommonCoreInjector() {
  return boost::di::make_injector(
      boost::di::bind<Config>().to<ConstMapConfig>().in(boost::di::singleton),
      boost::di::bind<FrameRateGovernor>().to<SleepFutureGovernor>());
}
}  // namespace impl
}  // namespace cubit
