#pragma once
#include <boost/di.hpp>

#include <cubit/os/Logger.h>
#include <cubit/os/SleepFuture.h>
#include <cubit/os/Timer.h>

namespace cubit {
namespace impl {

boost::di::injector<const TimerFactory&, const SleepFutureFactory&, Logger&>
getWin64OsComponent();
}  // namespace impl
}  // namespace cubit
