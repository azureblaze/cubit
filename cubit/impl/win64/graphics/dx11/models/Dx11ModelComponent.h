#pragma once

#include <fruit/fruit.h>

#include <cubit/Inject/Factory.h>

namespace cubit {
namespace impl {
struct Dx11Device;
struct Dx11DeviceContext;
class Dx11VertexBuffer;
class Dx11Resources;
class DebugAxis;
using Dx11ModelComponent = fruit::Component<
    fruit::Required<
        Dx11Device,
        Dx11DeviceContext,
        Factory<Dx11VertexBuffer, size_t>>,
    Factory<DebugAxis, Dx11Resources*>>;
Dx11ModelComponent getDx11ModelComponent();
}  // namespace impl
}  // namespace cubit
