#include "Win64OsComponent.h"

#include <boost/di/extension/injections/factory.hpp>

#include "QPCTimer.h"
#include "VCDebugLogger.h"
#include "WaitableTimerSleepFuture.h"

namespace di = boost::di;
namespace cubit {
namespace impl {

boost::di::injector<const TimerFactory&, const SleepFutureFactory&, Logger&>
getWin64OsComponent() {
  return di::make_injector(
      di::bind<TimerFactory>().to(di::extension::factory<QPCTimer>{}),
      di::bind<SleepFutureFactory>().to(
          di::extension::factory<WaitableTimerSleepFuture>{}),
      di::bind<Logger>().to<VCDebugLogger>());
}

}  // namespace impl
}  // namespace cubit
