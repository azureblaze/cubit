#pragma once
#include <fruit/fruit.h>

#include <cubit/Inject/Factory.h>
#include <cubit/os/Logger.h>
#include <cubit/os/SleepFuture.h>
#include <cubit/os/Timer.h>

namespace cubit {
namespace impl {

using Win64OsComponent =
    fruit::Component<Factory<Timer>, Factory<SleepFuture>, Logger>;
Win64OsComponent getWin64OsComponent();
}  // namespace impl
}  // namespace cubit
