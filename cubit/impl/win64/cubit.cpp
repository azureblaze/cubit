#include <cubit/cubit.h>

#include <boost/di/extension/injections/extensible_injector.hpp>

#include <memory>

#include <cubit/core/application.h>
#include <cubit/os/Logger.h>

#include "win64/core/Win64CoreComponent.h"
#include "win64/graphics/dx11/Dx11GraphicComponent.h"
#include "win64/graphics/dx11/Dx11Renderer.h"
#include "win64/input/Win64InputComponent.h"
#include "win64/os/Win64OsComponent.h"

namespace cubit {
boost::di::injector<Application&, Logger&, Renderer&, Input&> getCubitInjector(
    intptr_t instance,
    std::string_view commandLine) {
  return boost::di::make_injector(
      impl::getWin64OsComponent(),
      impl::getWin64CoreInjector(instance, commandLine),
      impl::getDx11GraphicsComponent(),
      impl::getWin64InputComponent());
}
}  // namespace cubit
