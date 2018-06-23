#include <cubit/cubit.h>

#include <cubit/core/application.h>
#include <memory>
#include "win64/core/Win64CoreComponent.h"
#include "win64/os/Win64OsComponent.h"
namespace cubit {
boost::di::injector<Application&, Logger&> getCubitInjector(
    intptr_t instance,
    std::string_view commandLine) {
  return boost::di::make_injector(
      impl::getWin64OsComponent(),
      impl::getWin64CoreInjector(instance, commandLine));
}
}  // namespace cubit
