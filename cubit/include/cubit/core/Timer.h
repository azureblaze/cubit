#pragma once

#include <boost/di/extension/injections/factory.hpp>

namespace cubit {
class Timer {
 public:
  virtual ~Timer() = default;
  virtual void start() = 0;
  virtual float get() = 0;
};

using TimerFactory = boost::di::extension::ifactory<Timer>;
}  // namespace cubit
