#include "Dx11Renderer.h"

#include <map>
#include <stdexcept>

#include <d3d11.h>
#include <dxgi1_3.h>

#include <cubit/config/Config.h>
#include <cubit/inject/InjectorFor.h>
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

namespace cubit {
namespace impl {

struct Dx11Renderer::Impl {
  std::map<Win64Window*, ComPtr<IDXGISwapChain1>> swapChains;

  Impl() {}
};

Dx11Renderer::Dx11Renderer(
    Config& config,
    Logger& logger,
    Dx11Device& device,
    Dx11Resources& resources,
    Factory<Dx11RenderTarget, std::shared_ptr<Dx11Texture2D>> targetFactory)
    : config(config),
      logger(logger),
      device(device),
      resources(resources),
      targetFactory(targetFactory) {
  impl = make_unique<Impl>();
}

Dx11Renderer::~Dx11Renderer() {}

void Dx11Renderer::present(Win64Window& window) {
  impl->swapChains[&window]->Present(0, 0);
}

cubit::Resources& Dx11Renderer::getResources() { return resources; }

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
      &device.getDevice(),
      (HWND)window.getHandle(),
      &swapChainDescription,
      nullptr,
      nullptr,
      &swapChain));

  auto texture = make_shared<Dx11Texture2D>(width, height);
  checkResult(swapChain->GetBuffer(
      0, __uuidof(ID3D11Texture2D), (void**)texture->texture.GetAddressOf()));

  unique_ptr<Dx11RenderTarget> target = targetFactory(texture);

  impl->swapChains[&window] = swapChain;
  return target;
}

}  // namespace impl
}  // namespace cubit
