#include "dx11GraphicComponent.h"

#include <cubit/config/config.h>
#include <cubit/os/Logger.h>

#include "win64/graphics/Win64Renderer.h"
#include "win64/graphics/dx11/Dx11Renderer.h"

namespace cubit {
namespace impl {

Dx11GraphicComponent getDx11GraphicsComponent() {
  return fruit::createComponent()
      .bind<Renderer, Dx11Renderer>()
      .bind<Win64Renderer, Dx11Renderer>();
}

}  // namespace impl
}  // namespace cubit
