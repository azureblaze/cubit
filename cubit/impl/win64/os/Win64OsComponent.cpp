#include "Win64OsComponent.h"

#include "QPCTimer.h"
#include "VCDebugLogger.h"
#include "WaitableTimerSleepFuture.h"

using namespace std;

namespace cubit {
namespace impl {

Win64OsComponent getWin64OsComponent() {
  return fruit::createComponent()
      .bind<Timer, QPCTimer>()
      .bind<SleepFuture, WaitableTimerSleepFuture>()
      .bind<Logger, VCDebugLogger>();
}

}  // namespace impl
}  // namespace cubit
