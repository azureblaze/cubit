#pragma once
#include <boost/di/extension/injections/factory.hpp>
namespace cubit {
class SleepFuture {
 public:
  virtual ~SleepFuture() = default;
  virtual void start(int64_t millis) = 0;
  virtual void get() = 0;
};

using SleepFutureFactory = boost::di::extension::ifactory<SleepFuture>;
}  // namespace cubit
