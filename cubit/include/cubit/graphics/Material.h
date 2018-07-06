#pragma once

namespace cubit {
class Scene;
class Material {
 public:
  virtual ~Material() = default;

  virtual void begin(const Scene& scene) = 0;
  virtual void end() = 0;
};
}  // namespace cubit
