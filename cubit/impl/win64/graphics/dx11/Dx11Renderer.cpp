#include "Dx11Renderer.h"

#include <stdexcept>

#include <d3d11.h>

#include <cubit/config/Config.h>
#include <cubit/os/Logger.h>

#include "dxresult.h"
#include "win64/core/Win64Window.h"

#include "Dx11InternalComponent.h"
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

struct Dx11Renderer::Impl {
  Logger& logger;
  Win64Window* window;

  Dx11InternalComponent component;

  Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
  Microsoft::WRL::ComPtr<ID3D11Device> device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

  std::unique_ptr<Dx11RenderTarget> backbufferTarget;

  std::unique_ptr<Dx11VertexShader> vertexShader;
  std::unique_ptr<Dx11PixelShader> pixelShader;

  Impl(Logger& logger, Win64Window* window, Dx11InternalComponent component)
      : logger(logger), window(window), component(move(component)) {}
};

Dx11Renderer::Dx11Renderer(
    Win64Window* window,
    Config& config,
    Logger& logger) {
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

  IDXGISwapChain* swapChain;
  ID3D11Device* device;
  ID3D11DeviceContext* deviceContext;

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

  impl = make_unique<Impl>(
      logger,
      window,
      getDx11InternalComponent(
          Dx11Device(device), Dx11DeviceContext(deviceContext)));
  impl->swapChain = swapChain;
  impl->device = device;
  impl->deviceContext = deviceContext;

  ComPtr<ID3D11Texture2D> backBufferTexture;
  checkResult(impl->swapChain->GetBuffer(
      0, __uuidof(ID3D11Texture2D), (void**)backBufferTexture.GetAddressOf()));
  impl->backbufferTarget =
      make_unique<Dx11RenderTarget>(impl->deviceContext.Get());
  checkResult(impl->device->CreateRenderTargetView(
      backBufferTexture.Get(),
      NULL,
      impl->backbufferTarget->target.GetAddressOf()));
  impl->deviceContext->OMSetRenderTargets(
      1, impl->backbufferTarget->target.GetAddressOf(), NULL);

  D3D11_VIEWPORT viewport{};
  viewport.Width = (float)window->getWidth();
  viewport.Height = (float)window->getHeight();

  impl->deviceContext->RSSetViewports(1, &viewport);

  auto vertexShaderFactory = impl->component.create<Dx11VertexShaderFactory>();
  auto pixelShaderFactory = impl->component.create<Dx11PixelShaderFactory>();

  impl->vertexShader =
      vertexShaderFactory(Shader::Spec{"data/default.hlsl", "vertexMain"});

  impl->pixelShader =
      pixelShaderFactory(Shader::Spec{"data/default.hlsl", "pixelMain"});

  impl->vertexShader->activate();
  impl->pixelShader->activate();
}

Dx11Renderer::~Dx11Renderer() {}

cubit::RenderTarget& Dx11Renderer::getBackBufferTarget() {
  return *impl->backbufferTarget;
}

void Dx11Renderer::present() { impl->swapChain->Present(0, 0); }

}  // namespace impl
}  // namespace cubit
