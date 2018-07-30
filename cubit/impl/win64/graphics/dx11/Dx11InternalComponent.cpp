#include "Dx11InternalComponent.h"

#include <boost/di/extension/injections/assisted_injection.hpp>

#include <string>

#include "common/inject/CommonInjectComponent.h"

#include "Dx11Device.h"
#include "Dx11Material.h"
#include "Dx11PixelShader.h"
#include "Dx11RenderTarget.h"
#include "Dx11Resources.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"
#include "models/DebugAxis.h"
#include "models/Dx11ModelsRegistry.h"

namespace di = boost::di;
using namespace std;

namespace cubit {
namespace impl {

Dx11InternalComponent getDx11InternalComponent(
    Dx11Device& device,
    Dx11DeviceContext& deviceContext) {
  auto injector = di::make_injector(
      getCommonInjectComponent(),
      di::bind<Dx11Device>().to(device),
      di::bind<Dx11DeviceContext>().to(deviceContext),
      di::bind<Factory<Dx11VertexShader, const ShaderSpec&>>().to(
          di::extension::assisted_injection<Dx11VertexShader>{}),
      di::bind<Factory<Dx11PixelShader, const ShaderSpec&>>().to(
          di::extension::assisted_injection<Dx11PixelShader>{}),
      di::bind<Factory<Dx11VertexBuffer, size_t>>().to(
          di::extension::assisted_injection<Dx11VertexBuffer>{}),
      di::bind<Factory<Dx11Material>>().to(
          di::extension::assisted_injection<Dx11Material>{}),
      di::bind<Factory<DebugAxis>>().to(
          di::extension::assisted_injection<DebugAxis>{}),
      di::bind<Factory<Dx11RenderTarget, std::shared_ptr<Dx11Texture2D>>>().to(
          di::extension::assisted_injection<Dx11RenderTarget>{}),
      di::bind<Dx11ModelsRegistry>().to<Dx11ModelsRegistry>().in(
          di::singleton));

  return injector;
}
}  // namespace impl
}  // namespace cubit
