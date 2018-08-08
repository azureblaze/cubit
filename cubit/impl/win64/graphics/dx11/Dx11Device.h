#pragma once

#include <fruit/fruit.h>

#include "ComPtr.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
namespace cubit {
namespace impl {

class Dx11Device {
  ComPtr<ID3D11Device> device;
  ComPtr<ID3D11DeviceContext> deviceContext;

 public:
  INJECT(Dx11Device());
  ~Dx11Device();

  ID3D11Device& getDevice() { return *device; }
  ID3D11DeviceContext& getDeviceContext() { return *deviceContext; }
};

}  // namespace impl
}  // namespace cubit
