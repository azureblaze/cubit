#include "Dx11ModelsRegistry.h"

#include <cubit/Inject/FactoryRegistry.h>

#include "DebugAxis.h"

using namespace std;

namespace cubit {

namespace impl {

static Factory<DebugAxis> f;

Dx11ModelsRegistry::Dx11ModelsRegistry(
    std::shared_ptr<FactoryRegistry> registry,
    Factory<DebugAxis> debugAxisFactory) {
  registry->registerFactory<Dx11Model>(std::string("debug:axis"), [=]() {
    return unique_ptr<Dx11Model>(debugAxisFactory());
  });
}

}  // namespace impl
}  // namespace cubit
