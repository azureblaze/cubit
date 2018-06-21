#include <cubit/cubit.h>

#include <cubit/core/application.h>
#include <memory>
#include "win64/core/Win64CoreComponent.h"
namespace cubit {
boost::di::injector<Application&, Logger&> getCubitInjector(
    intptr_t instance,
    std::string_view commandLine) {
  return boost::di::make_injector(
      cubit::impl::getWin64CoreInjector(instance, commandLine));
}
}  // namespace cubit
