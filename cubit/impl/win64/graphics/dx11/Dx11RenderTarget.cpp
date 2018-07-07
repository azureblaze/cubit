#include "Dx11RenderTarget.h"

#include <d3d11.h>

#include <cubit/graphics/color.h>

#include "Dx11Texture2D.h"
#include "DxResult.h"

namespace cubit {
namespace impl {
Dx11RenderTarget::Dx11RenderTarget(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    std::shared_ptr<Dx11Texture2D> texture)
    : deviceContext(deviceContext), texture(texture) {
  checkResult(device->CreateRenderTargetView(
      texture->texture.Get(), NULL, target.GetAddressOf()));
}

Dx11RenderTarget::~Dx11RenderTarget() {}

void Dx11RenderTarget::clear(Color color) {
  deviceContext->ClearRenderTargetView(target.Get(), (float*)&color);
}

void Dx11RenderTarget::bind() {
  deviceContext->OMSetRenderTargets(1, target.GetAddressOf(), NULL);

  D3D11_VIEWPORT viewport{};
  viewport.Width = texture->getWidth();
  viewport.Height = texture->getHeight();
  viewport.MaxDepth = 1.0f;

  deviceContext->RSSetViewports(1, &viewport);
}

}  // namespace impl
}  // namespace cubit
