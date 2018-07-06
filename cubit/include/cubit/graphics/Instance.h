#pragma once
#include <functional>

//#include "Transform.h"

namespace cubit {
class Model;

class Instance {
 public:
  virtual ~Instance() = default;

  virtual const Model* getModel() const = 0;
};
}  // namespace cubit
