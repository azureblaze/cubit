#include "CommonInjectComponent.h"

#include <cubit/inject/FactoryRegistry.h>

#include "FactoryRegistryImpl.h"

namespace cubit {
namespace impl {
CommonInjectComponent getCommonInjectComponent() {
  return fruit::createComponent().bind<FactoryRegistry, FactoryRegistryImpl>();
}
}  // namespace impl
}  // namespace cubit
