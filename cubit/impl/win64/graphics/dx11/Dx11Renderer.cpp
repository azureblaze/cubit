#include "Dx11Renderer.h"

#include <map>
#include <stdexcept>

#include <d3d11.h>
#include <dxgi1_3.h>

#include <cubit/config/Config.h>
#include <cubit/os/Logger.h>

#include "dxresult.h"
#include "win64/core/Win64Window.h"

#include "Dx11InternalComponent.h"
#include "Dx11PixelShader.h"
#include "Dx11RenderTarget.h"
#include "Dx11Resources.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexShader.h"

#include "Dx11VertexBuffer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "Dxgi.lib")

using namespace std;
using namespace Microsoft::WRL;

namespace cubit {
namespace impl {

struct Dx11Renderer::Impl {
  Logger& logger;
  Config& config;

  Dx11InternalComponent component;

  Microsoft::WRL::ComPtr<ID3D11Device> device;
  Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

  std::unique_ptr<Dx11Resources> resources;

  std::map<Win64Window*, ComPtr<IDXGISwapChain1>> swapChains;

  Impl(Config& config, Logger& logger, Dx11InternalComponent component)
      : config(config), logger(logger), component(move(component)) {}
};

Dx11Renderer::Dx11Renderer(Config& config, Logger& logger) {
  ID3D11Device* device;
  ID3D11DeviceContext* deviceContext;

  checkResult(D3D11CreateDevice(
      NULL,
      D3D_DRIVER_TYPE_HARDWARE,
      NULL,
      D3D11_CREATE_DEVICE_DEBUG,
      NULL,
      NULL,
      D3D11_SDK_VERSION,
      &device,
      NULL,
      &deviceContext));

  impl = make_unique<Impl>(
      config,
      logger,
      getDx11InternalComponent(
          Dx11Device(device), Dx11DeviceContext(deviceContext)));
  impl->device = device;
  impl->deviceContext = deviceContext;
  impl->resources = impl->component.create<unique_ptr<Dx11Resources>>();
}

Dx11Renderer::~Dx11Renderer() {}

void Dx11Renderer::present(Win64Window& window) {
  impl->swapChains[&window]->Present(0, 0);
}

cubit::Resources& Dx11Renderer::resources() { return *(impl->resources.get()); }

unique_ptr<RenderTarget> Dx11Renderer::createTarget(Win64Window& window) {
  IDXGISwapChain1* swapChain;

  int width = window.getWidth();
  int height = window.getHeight();
  DXGI_SWAP_CHAIN_DESC1 swapChainDescription{};
  swapChainDescription.BufferCount = 1;
  swapChainDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDescription.Width = width;
  swapChainDescription.Height = height;
  swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDescription.SampleDesc.Count = 1;
  swapChainDescription.SampleDesc.Quality = 0;

  ComPtr<IDXGIFactory2> factory;
  CreateDXGIFactory2(
      DXGI_CREATE_FACTORY_DEBUG,
      __uuidof(IDXGIFactory2),
      (void**)factory.GetAddressOf());

  checkResult(factory->CreateSwapChainForHwnd(
      impl->device.Get(),
      (HWND)window.getHandle(),
      &swapChainDescription,
      nullptr,
      nullptr,
      &swapChain));

  auto texture = make_shared<Dx11Texture2D>(width, height);
  checkResult(swapChain->GetBuffer(
      0, __uuidof(ID3D11Texture2D), (void**)texture->texture.GetAddressOf()));

  Dx11RenderTargetFactory targetFactory =
      impl->component.create<Dx11RenderTargetFactory>();

  unique_ptr<Dx11RenderTarget> target = targetFactory(texture);

  impl->swapChains[&window] = swapChain;
  return target;
}

}  // namespace impl
}  // namespace cubit
