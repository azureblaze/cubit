#include <cubit/core/FrameUpdateMetrics.h>
#include <cubit/core/SleepFuture.h>
#include <cubit/core/Timer.h>
#include <cubit/core/config.h>
#include <memory>
#include "QPCTimer.h"
#include "VCDebugLogger.h"
#include "WaitableTimerSleepFuture.h"
#include "Win64Application.h"
#include "Win64CoreComponent.h"
#include "Win64Window.h"
#include "common/core/CommonCoreComponent.h"
#include "common/core/ConstMapConfig.h"

namespace di = boost::di;
using namespace std;

namespace cubit {
namespace impl {
di::injector<Application&, Logger&> getWin64CoreInjector(
    intptr_t applicationInstance,
    string_view commandLineArgs) {
  return di::make_injector(
      getCommonCoreInjector(),
      di::bind<Application>().to<Win64Application>(),
      di::bind<Win64Application::Spec>().to(
          Win64Application::Spec{applicationInstance, commandLineArgs}),
      di::bind<di::extension::ifactory<Win64Window, Win64Window::Spec>>().to(
          di::extension::factory<Win64Window>{}),
      di::bind<TimerFactory>().to(di::extension::factory<QPCTimer>{}),
      di::bind<SleepFutureFactory>().to(
          di::extension::factory<WaitableTimerSleepFuture>{}),
      di::bind<Logger>().to<VCDebugLogger>());
}
}  // namespace impl
}  // namespace cubit
