#pragma once
#include <string>

namespace cubit {
class Shader {
 public:
  struct Spec {
    std::string file;
    std::string entryPoint;
  };

  virtual void activate() = 0;
};
}  // namespace cubit
