#include "Dx11Renderer.h"

#include <stdexcept>

#include <d3d11.h>

#include <cubit/os/Logger.h>

#include "win64/core/Win64Window.h"

#pragma comment(lib, "d3d11.lib")

namespace cubit {
namespace impl {
Dx11Renderer::Dx11Renderer(Logger& logger, Win64Window* window)
    : logger(logger), window(window) {
  DXGI_SWAP_CHAIN_DESC swapChainDescription;

  swapChainDescription.BufferCount = 1;
  swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDescription.OutputWindow = (HWND)window->getHandle();
  swapChainDescription.SampleDesc.Count = 4;
  swapChainDescription.Windowed = TRUE;

  D3D11CreateDeviceAndSwapChain(
      NULL,
      D3D_DRIVER_TYPE_HARDWARE,
      NULL,
      NULL,
      NULL,
      NULL,
      D3D11_SDK_VERSION,
      &swapChainDescription,
      &swapChain,
      &device,
      NULL,
      &deviceContext);
}

void Dx11Renderer::present() {
  logger.stream() << "present"
                  << "\n";
}

}  // namespace impl
}  // namespace cubit
