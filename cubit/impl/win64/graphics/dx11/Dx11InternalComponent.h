#pragma once
#include <memory>

#include <fruit/fruit.h>

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
class Dx11Device;
class Dx11DeviceContext;
class Dx11Resources;
class Dx11ModelsRegistry;

using Dx11InternalComponent = fruit::Component<
    Factory<Dx11VertexShader, const ShaderSpec&>,
    Factory<Dx11PixelShader, const ShaderSpec&>,
    Factory<Dx11VertexBuffer, size_t>,
    Factory<Dx11RenderTarget, std::shared_ptr<Dx11Texture2D>>,
    Factory<Dx11Material, Dx11Resources*>,
    Dx11Device,
    Dx11Resources>;

Dx11InternalComponent getDx11InternalComponent();

}  // namespace impl
}  // namespace cubit
