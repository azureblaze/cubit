#pragma once

#include <string>

namespace cubit {
class Model;
class Resources {
 public:
  virtual const Model* getModel(const std::string& name) = 0;
};
}  // namespace cubit
