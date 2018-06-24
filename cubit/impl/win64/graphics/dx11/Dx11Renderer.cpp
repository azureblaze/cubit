#include "Dx11Renderer.h"

#include <stdexcept>

#include <d3d11.h>

#include <cubit/os/Logger.h>

#include "dxresult.h"
#include "win64/core/Win64Window.h"
#include "win64/graphics/dx11/Dx11RenderTarget.h"
#include "win64/graphics/dx11/Dx11Texture2D.h"

#pragma comment(lib, "d3d11.lib")

using namespace std;

namespace cubit {
namespace impl {
Dx11Renderer::Dx11Renderer(Logger& logger, Win64Window* window)
    : logger(logger), window(window) {
  DXGI_SWAP_CHAIN_DESC swapChainDescription{};

  swapChainDescription.BufferCount = 1;
  swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDescription.OutputWindow = (HWND)window->getHandle();
  swapChainDescription.SampleDesc.Count = 4;
  swapChainDescription.Windowed = TRUE;

  checkResult(D3D11CreateDeviceAndSwapChain(
      NULL,
      D3D_DRIVER_TYPE_HARDWARE,
      NULL,
      D3D11_CREATE_DEVICE_DEBUG,
      NULL,
      NULL,
      D3D11_SDK_VERSION,
      &swapChainDescription,
      &swapChain,
      &device,
      NULL,
      &deviceContext));

  auto backBufferTexture = make_unique<Dx11Texture2D>();
  swapChain->GetBuffer(
      0, __uuidof(ID3D11Texture2D), (void**)&backBufferTexture->texture);
  backbufferTarget = make_unique<Dx11RenderTarget>(deviceContext);
  device->CreateRenderTargetView(
      backBufferTexture->texture, NULL, &backbufferTarget->target);
  deviceContext->OMSetRenderTargets(1, &backbufferTarget->target, NULL);

  D3D11_VIEWPORT viewport{};
  viewport.Width = (float)window->getWidth();
  viewport.Height = (float)window->getHeight();

  deviceContext->RSSetViewports(1, &viewport);
}

Dx11Renderer::~Dx11Renderer() {
  swapChain->Release();
  device->Release();
  deviceContext->Release();
}

cubit::RenderTarget& Dx11Renderer::getBackBufferTarget() {
  return *backbufferTarget;
}

void Dx11Renderer::present() { swapChain->Present(0, 0); }

}  // namespace impl
}  // namespace cubit
