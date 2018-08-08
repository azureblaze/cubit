#pragma once

#include <memory>
#include <string>

#include "Factory.h"

namespace cubit {
template <class T, class... Args>
class FactoryEntry {
 public:
  virtual ~FactoryEntry() = default;

  virtual const std::string key() const = 0;

  virtual Factory<T, Args...> value() = 0;
};
}  // namespace cubit
