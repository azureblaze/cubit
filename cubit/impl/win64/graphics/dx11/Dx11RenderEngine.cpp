#include "Dx11RenderEngine.h"

#include <stdexcept>

#include <d3d11.h>
#include <d3dx10.h>
#include <d3dx11.h>

#include <cubit/os/Logger.h>

#include "win64/core/Win64Window.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

namespace cubit {
namespace impl {
Dx11RenderEngine::Dx11RenderEngine(Logger& logger, Win64Window* window)
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

void Dx11RenderEngine::present() {
  logger.stream() << "present"
                  << "\n";
}

}  // namespace impl
}  // namespace cubit
