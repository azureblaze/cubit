#include "Dx11InternalComponent.h"

#include <boost/di/extension/injections/assisted_injection.hpp>

#include <string>

#include "Dx11Material.h"
#include "Dx11Resources.h"

namespace di = boost::di;
using namespace std;

namespace cubit {
namespace impl {

Dx11InternalComponent getDx11InternalComponent(
    Dx11Device device,
    Dx11DeviceContext deviceContext) {
  auto d = std::make_shared<Dx11Device>(device);
  auto dc = std::make_shared<Dx11DeviceContext>(deviceContext);

  return di::make_injector(
      di::bind<Dx11Device>().to(d),
      di::bind<Dx11DeviceContext>().to(dc),
      di::bind<Dx11VertexShaderFactory>().to(
          di::extension::assisted_injection<Dx11VertexShader>{}),
      di::bind<Dx11PixelShaderFactory>().to(
          di::extension::assisted_injection<Dx11PixelShader>{}),
      di::bind<Dx11VertexBufferFactory>().to(
          di::extension::assisted_injection<Dx11VertexBuffer>{}),
      di::bind<DebugAxisFactory>().to(
          di::extension::assisted_injection<DebugAxis>{}),
      di::bind<Dx11RenderTargetFactory>().to(
          di::extension::assisted_injection<Dx11RenderTarget>{}));
}
}  // namespace impl
}  // namespace cubit
