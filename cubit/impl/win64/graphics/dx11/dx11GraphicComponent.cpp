#include "dx11GraphicComponent.h"

#include <cubit/config/config.h>
#include <cubit/inject/FactoryRegistry.h>
#include <cubit/os/Logger.h>

#include "win64/graphics/Win64Renderer.h"

#include "Dx11InternalComponent.h"
#include "Dx11RenderTarget.h"
#include "Dx11Renderer.h"
#include "Dx11Resources.h"

namespace cubit {
namespace impl {

Dx11GraphicComponent getDx11GraphicsComponent() {
  return fruit::createComponent()
      .install(getDx11InternalComponent)
      .bind<Renderer, Dx11Renderer>()
      .bind<Win64Renderer, Dx11Renderer>();
}

}  // namespace impl
}  // namespace cubit
