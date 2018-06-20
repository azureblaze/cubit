#pragma once
#include <cubit/core/SleepFuture.h>

namespace cubit {
namespace impl {
class WaitableTimerSleepFuture : public SleepFuture {
 public:
  WaitableTimerSleepFuture();
  ~WaitableTimerSleepFuture();
  void start(int64_t millis);
  void get();

 private:
  int64_t sleepMillis;
  void* timer = nullptr;
};
}  // namespace impl
}  // namespace cubit
