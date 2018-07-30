#pragma once
#include <memory>

#include <boost/di.hpp>

#include <cubit/inject/factory.h>

namespace cubit {
struct ShaderSpec;
namespace impl {

class Dx11VertexShader;
class Dx11PixelShader;
class Dx11VertexBuffer;
class Dx11RenderTarget;
class Dx11Texture2D;
class Dx11Material;
class DebugAxis;
struct Dx11Device;
struct Dx11DeviceContext;
class Dx11Resources;
class Dx11ModelsRegistry;

using Dx11InternalComponent = boost::di::injector<
    Factory<Dx11VertexShader, const ShaderSpec&>,
    Factory<Dx11PixelShader, const ShaderSpec&>,
    Factory<Dx11VertexBuffer, size_t>,
    Factory<Dx11RenderTarget, std::shared_ptr<Dx11Texture2D>>,
    Factory<Dx11Material>,
    Dx11Device,
    std::unique_ptr<Dx11Resources>,
    Factory<DebugAxis>,
    std::shared_ptr<Dx11ModelsRegistry>>;

Dx11InternalComponent getDx11InternalComponent(
    Dx11Device& device,
    Dx11DeviceContext& deviceContext);

}  // namespace impl
}  // namespace cubit
