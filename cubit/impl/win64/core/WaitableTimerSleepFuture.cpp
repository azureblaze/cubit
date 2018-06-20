#include "WaitableTimerSleepFuture.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")

namespace cubit {
namespace impl {
WaitableTimerSleepFuture::WaitableTimerSleepFuture() {
  timer = CreateWaitableTimer(nullptr, NULL, nullptr);
}
WaitableTimerSleepFuture::~WaitableTimerSleepFuture() { CloseHandle(timer); }

void WaitableTimerSleepFuture::start(int64_t millis) {
  sleepMillis = millis;
  if (sleepMillis <= 0) {
    return;
  }
  LARGE_INTEGER hecto_nano_seconds;  // the unit for SetWaitableTimer is 100ns
  hecto_nano_seconds.QuadPart =
      millis * 1000LL * 10LL * -1;  // negative for relative time
  SetWaitableTimer(timer, &hecto_nano_seconds, 0, nullptr, nullptr, FALSE);
}

void WaitableTimerSleepFuture::get() {
  if (sleepMillis <= 0) {
    return;
  }
  WaitForSingleObject(timer, INFINITE);
}

}  // namespace impl
}  // namespace cubit
