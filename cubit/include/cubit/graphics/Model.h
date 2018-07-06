#pragma once

#include <memory>
#include <set>

namespace cubit {
class Material;
class Instance;

class Model {
 public:
  virtual ~Model() = default;

  virtual Material* getMaterial() const = 0;

  virtual std::unique_ptr<Instance> createInstance() const = 0;

  virtual void drawPrimitives(const std::set<Instance*>& instances) const = 0;
};
}  // namespace cubit
