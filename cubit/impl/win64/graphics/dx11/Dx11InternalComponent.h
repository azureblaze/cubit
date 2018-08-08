#pragma once
#include <memory>

#include <fruit/fruit.h>

#include <cubit/inject/factory.h>

namespace cubit {
struct ShaderSpec;
class FactoryRegistry;
namespace impl {

class Dx11RenderTarget;
class Dx11Texture2D;
class Dx11Device;
class Dx11Resources;

using Dx11InternalComponent = fruit::Component<
    fruit::Required<FactoryRegistry>,
    Factory<Dx11RenderTarget, std::shared_ptr<Dx11Texture2D>>,
    Dx11Device,
    Dx11Resources>;

Dx11InternalComponent getDx11InternalComponent();

}  // namespace impl
}  // namespace cubit
