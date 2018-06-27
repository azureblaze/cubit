#include "Dx11InternalComponent.h"

#include <boost/di/extension/injections/assisted_injection.hpp>

#include <string>
namespace di = boost::di;
using namespace std;

namespace cubit {
namespace impl {

Dx11InternalComponent getDx11InternalComponent(
    Dx11Device device,
    Dx11DeviceContext deviceContext) {
  return di::make_injector(
      di::bind<Dx11Device>().to(device),
      di::bind<Dx11DeviceContext>().to(deviceContext),
      di::bind<Dx11VertexShaderFactory>().to(
          di::extension::assisted_injection<Dx11VertexShader>{}),
      di::bind<Dx11PixelShaderFactory>().to(
          di::extension::assisted_injection<Dx11PixelShader>{}),
      di::bind<Dx11VertexBufferFactory>().to(
          di::extension::assisted_injection<Dx11VertexBuffer>{}));
}
}  // namespace impl
}  // namespace cubit
