#include "Dx11RenderTarget.h"

#include <d3d11.h>

#include <cubit/graphics/color.h>

namespace cubit {
namespace impl {

void Dx11RenderTarget::clear(Color color) {
  deviceContext->ClearRenderTargetView(target, (float*)&color);
}

Dx11RenderTarget::~Dx11RenderTarget() { target->Release(); }
}  // namespace impl
}  // namespace cubit
