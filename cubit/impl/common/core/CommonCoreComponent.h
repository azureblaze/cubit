#pragma once
#include <boost/di.hpp>
#include <memory>

#include "FrameRateGovernor.h"
#include "SleepFutureGovernor.h"
#include "common/config/CommonConfigComponent.h"
#include "win64/os/Win64OsComponent.h"

namespace cubit {
class Config;
namespace impl {
class ConstMapConfig;
boost::di::injector<std::unique_ptr<FrameRateGovernor>> getCommonCoreInjector();
}  // namespace impl
}  // namespace cubit
