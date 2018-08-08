#include "Dx11RenderTarget.h"

#include <d3d11.h>

#include <cubit/graphics/color.h>

#include "Dx11Texture2D.h"
#include "DxResult.h"

namespace cubit {
namespace impl {
Dx11RenderTarget::Dx11RenderTarget(
    Dx11Device* device,
    std::shared_ptr<Dx11Texture2D> texture)
    : device(device), texture(texture) {
  checkResult(device->getDevice().CreateRenderTargetView(
      texture->texture.Get(), NULL, target.GetAddressOf()));
}

Dx11RenderTarget::~Dx11RenderTarget() {}

void Dx11RenderTarget::clear(Color color) {
  device->getDeviceContext().ClearRenderTargetView(
      target.Get(), (float*)&color);
}

void Dx11RenderTarget::bind() {
  device->getDeviceContext().OMSetRenderTargets(1, target.GetAddressOf(), NULL);

  D3D11_VIEWPORT viewport{};
  viewport.Width = texture->getWidth();
  viewport.Height = texture->getHeight();
  viewport.MaxDepth = 1.0f;

  device->getDeviceContext().RSSetViewports(1, &viewport);
}

}  // namespace impl
}  // namespace cubit
