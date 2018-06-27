#pragma once
#include <memory>

#include <boost/di.hpp>

#include "Dx11Device.h"
#include "Dx11PixelShader.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"

namespace cubit {
namespace impl {

using Dx11InternalComponent = boost::di::injector<
    Dx11VertexShaderFactory,
    Dx11PixelShaderFactory,
    Dx11VertexBufferFactory>;

Dx11InternalComponent getDx11InternalComponent(
    Dx11Device device,
    Dx11DeviceContext deviceContext);

}  // namespace impl
}  // namespace cubit
