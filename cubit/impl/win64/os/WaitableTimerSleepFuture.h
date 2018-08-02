#pragma once
#include <cubit/os/SleepFuture.h>

#include <fruit/fruit.h>

namespace cubit {
namespace impl {
class WaitableTimerSleepFuture : public SleepFuture {
 public:
  INJECT(WaitableTimerSleepFuture());
  ~WaitableTimerSleepFuture();
  void start(int64_t millis);
  void get();

 private:
  int64_t sleepMillis;
  void* timer = nullptr;
};
}  // namespace impl
}  // namespace cubit
