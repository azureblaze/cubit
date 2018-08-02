#include "CommonConfigComponent.h"
#include "ConstMapConfig.h"

namespace cubit {
namespace impl {
fruit::Component<Config> cubit::impl::getCommonConfigComponent() {
  return fruit::createComponent().bind<Config, ConstMapConfig>();
}

}  // namespace impl
}  // namespace cubit
