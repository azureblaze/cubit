#include "dx11GraphicComponent.h"

#include "common/config/CommonConfigComponent.h"
#include "win64/graphics/Win64Renderer.h"
#include "win64/graphics/dx11/Dx11Renderer.h"
#include "win64/os/Win64OsComponent.h"
namespace di = boost::di;

namespace cubit {
namespace impl {

boost::di::injector<Win64Renderer&, Renderer&> getDx11GraphicsComponent() {
  return boost::di::make_injector(
      getCommonConfigComponent(),
      getWin64OsComponent(),
      boost::di::bind<Renderer, Win64Renderer>().to<Dx11Renderer>());
}

}  // namespace impl
}  // namespace cubit
