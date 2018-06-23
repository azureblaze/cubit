#include "dx11GraphicComponent.h"

#include "common/graphics/DirectRenderer.h"
#include "win64/graphics/Win64RenderEngine.h"
#include "win64/graphics/dx11/Dx11RenderEngine.h"
#include "win64/os/Win64OsComponent.h"
namespace di = boost::di;

namespace cubit {
namespace impl {

boost::di::injector<Win64RenderEngineFactory, RendererFactory>
getDx11GraphicsComponent() {
  return boost::di::make_injector(
      getWin64OsComponent(),
      boost::di::bind<Win64RenderEngineFactory>().to(
          boost::di::extension::assisted_injection<Dx11RenderEngine>{}),
      boost::di::bind<RendererFactory>().to(
          boost::di::extension::assisted_injection<DirectRenderer>{}));
}

}  // namespace impl
}  // namespace cubit
