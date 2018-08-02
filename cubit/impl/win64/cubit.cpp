#include <cubit/cubit.h>

#include <memory>

#include <cubit/core/application.h>
#include <cubit/os/Logger.h>

#include "common/config/CommonConfigComponent.h"
#include "common/core/CommonCoreComponent.h"
#include "win64/core/Win64CoreComponent.h"
#include "win64/graphics/dx11/Dx11GraphicComponent.h"
#include "win64/graphics/dx11/Dx11Renderer.h"
#include "win64/input/Win64InputComponent.h"
#include "win64/os/Win64OsComponent.h"

namespace cubit {
CubitComponent getCubitInjector() {
  return fruit::createComponent()
      .install(impl::getCommonConfigComponent)
      .install(impl::getCommonCoreInjector)
      .install(impl::getWin64OsComponent)
      .install(impl::getWin64CoreInjector)
      .install(impl::getDx11GraphicsComponent)
      .install(impl::getWin64InputComponent);
}
}  // namespace cubit
