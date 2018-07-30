#include "CommonInjectComponent.h"

#include "FactoryRegistryImpl.h"

namespace di = boost::di;

namespace cubit {
di::injector<std::shared_ptr<FactoryRegistry>> getCommonInjectComponent() {
  return di::make_injector(
      di::bind<FactoryRegistry>().to<impl::FactoryRegistryImpl>().in(
          di::singleton));
}

}  // namespace cubit
