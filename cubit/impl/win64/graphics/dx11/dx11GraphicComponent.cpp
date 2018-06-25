#include "dx11GraphicComponent.h"

#include "common/config/CommonConfigComponent.h"
#include "win64/graphics/Win64Renderer.h"
#include "win64/graphics/dx11/Dx11Renderer.h"
#include "win64/os/Win64OsComponent.h"
namespace di = boost::di;

namespace cubit {
namespace impl {

boost::di::injector<Win64RendererFactory> getDx11GraphicsComponent() {
  return boost::di::make_injector(
      getCommonConfigComponent(),
      getWin64OsComponent(),
      boost::di::bind<Win64RendererFactory>().to(
          boost::di::extension::assisted_injection<Dx11Renderer>{}));
}

}  // namespace impl
}  // namespace cubit
