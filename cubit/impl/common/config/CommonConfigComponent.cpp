#include "CommonConfigComponent.h"
#include "ConstMapConfig.h"

namespace cubit {
namespace impl {
boost::di::injector<Config&> cubit::impl::getCommonConfigComponent() {
  return boost::di::make_injector(
      boost::di::bind<Config>().to<ConstMapConfig>());
}

}  // namespace impl
}  // namespace cubit
