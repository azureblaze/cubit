#include "Dx11RenderTarget.h"

#include <d3d11.h>

#include <cubit/graphics/color.h>

namespace cubit {
namespace impl {

void Dx11RenderTarget::clear(Color color) {
  deviceContext->ClearRenderTargetView(target.Get(), (float*)&color);
}

Dx11RenderTarget::~Dx11RenderTarget() {}

}  // namespace impl
}  // namespace cubit
