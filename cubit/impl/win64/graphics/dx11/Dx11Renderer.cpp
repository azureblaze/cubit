#include "Dx11Renderer.h"

#include <stdexcept>

#include <d3d11.h>

#include <cubit/config/Config.h>
#include <cubit/os/Logger.h>

#include "dxresult.h"
#include "win64/core/Win64Window.h"

#include "Dx11PixelShader.h"
#include "Dx11RenderTarget.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexShader.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

using namespace std;
using namespace Microsoft::WRL;

namespace cubit {
namespace impl {

Dx11Renderer::Dx11Renderer(Win64Window* window, Config& config, Logger& logger)
    : logger(logger), window(window) {
  int width = config.get<int>("default_window_width");
  int height = config.get<int>("default_window_height");
  DXGI_SWAP_CHAIN_DESC swapChainDescription{};
  swapChainDescription.BufferCount = 1;
  swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDescription.BufferDesc.Width = width;
  swapChainDescription.BufferDesc.Height = height;
  swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDescription.OutputWindow = (HWND)window->getHandle();
  swapChainDescription.SampleDesc.Count = 1;
  swapChainDescription.SampleDesc.Quality = 0;
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

  ComPtr<ID3D11Texture2D> backBufferTexture;
  checkResult(swapChain->GetBuffer(
      0, __uuidof(ID3D11Texture2D), (void**)backBufferTexture.GetAddressOf()));
  backbufferTarget = make_unique<Dx11RenderTarget>(deviceContext.Get());
  checkResult(device->CreateRenderTargetView(
      backBufferTexture.Get(), NULL, backbufferTarget->target.GetAddressOf()));
  deviceContext->OMSetRenderTargets(
      1, backbufferTarget->target.GetAddressOf(), NULL);

  D3D11_VIEWPORT viewport{};
  viewport.Width = (float)window->getWidth();
  viewport.Height = (float)window->getHeight();

  deviceContext->RSSetViewports(1, &viewport);

  vertexShader = make_unique<Dx11VertexShader>(
      Shader::Spec{"data/default.hlsl", "vertexMain"}, device.Get());

  pixelShader = make_unique<Dx11PixelShader>(
      Shader::Spec{"data/default.hlsl", "pixelMain"}, device.Get());
}

Dx11Renderer::~Dx11Renderer() {}

cubit::RenderTarget& Dx11Renderer::getBackBufferTarget() {
  return *backbufferTarget;
}

void Dx11Renderer::present() { swapChain->Present(0, 0); }

}  // namespace impl
}  // namespace cubit
