#pragma once
#include <cubit/os/Timer.h>
#include <stdint.h>

#include <fruit/fruit.h>

namespace cubit {
namespace impl {

class QPCFrequency {
 public:
  INJECT(QPCFrequency());
  operator int64_t() const { return frequency; }

 private:
  int64_t frequency;
};

class QPCTimer : public cubit::Timer {
 public:
  INJECT(QPCTimer(QPCFrequency frequency)) : frequency(frequency){};

  virtual void start() override;
  virtual float get() override;

 private:
  int64_t startTime;
  int64_t frequency;
};
}  // namespace impl
}  // namespace cubit
