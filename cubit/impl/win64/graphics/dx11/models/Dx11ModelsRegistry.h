#pragma once

#include <cubit/Inject/EagerSingleton.h>
#include <cubit/Inject/Factory.h>

namespace cubit {
class FactoryRegistry;
namespace impl {

class DebugAxis;
class Dx11ModelsRegistry : public EagerSingleton {
 public:
  Dx11ModelsRegistry(
      std::shared_ptr<FactoryRegistry> registry,
      Factory<DebugAxis> debugAxisFactory);
};

}  // namespace impl
}  // namespace cubit
