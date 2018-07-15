#pragma once
#include <string>

namespace cubit {
struct ShaderSpec {
  std::string file;
  std::string entryPoint;

  bool operator<(const ShaderSpec& rhs) const {
    return file < rhs.file || entryPoint < rhs.entryPoint;
  }
};
class Shader {
 public:
  virtual void activate() const = 0;
};
}  // namespace cubit
