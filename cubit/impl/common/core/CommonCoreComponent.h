#pragma once
#include <memory>

#include <fruit/fruit.h>

#include "FrameRateGovernor.h"
#include "SleepFutureGovernor.h"
#include "common/config/CommonConfigComponent.h"
#include "win64/os/Win64OsComponent.h"

namespace cubit {
class Config;
class Logger;
namespace impl {
class ConstMapConfig;
using CommonCoreComponent = fruit::Component<
    fruit::Required<Config, Logger, Factory<SleepFuture>, Factory<Timer>>,
    std::function<std::unique_ptr<FrameRateGovernor>()>>;

CommonCoreComponent getCommonCoreInjector();
}  // namespace impl
}  // namespace cubit
