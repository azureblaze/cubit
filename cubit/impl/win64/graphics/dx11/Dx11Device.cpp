#include "Dx11Device.h"

#include <d3d11.h>

#include "DxResult.h"

namespace cubit {
namespace impl {

Dx11Device::Dx11Device() {
  checkResult(D3D11CreateDevice(
      NULL,
      D3D_DRIVER_TYPE_HARDWARE,
      NULL,
      D3D11_CREATE_DEVICE_DEBUG,
      NULL,
      NULL,
      D3D11_SDK_VERSION,
      device.GetAddressOf(),
      NULL,
      deviceContext.GetAddressOf()));
}
Dx11Device::~Dx11Device(){}
}  // namespace impl
}  // namespace cubit
