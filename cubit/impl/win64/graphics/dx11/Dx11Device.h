#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
namespace cubit {
namespace impl {

struct Dx11Device {
  Dx11Device(ID3D11Device* rd) : device(rd) {}

  Dx11Device(const Dx11Device& d) : device(d.device){};

  ID3D11Device* device = nullptr;

  ID3D11Device* operator->() const { return device; };

  operator ID3D11Device*() const { return device; }
};

struct Dx11DeviceContext {
  Dx11DeviceContext(ID3D11DeviceContext* deviceContext)
      : deviceContext(deviceContext) {}

  Dx11DeviceContext(Dx11DeviceContext& d) : deviceContext(d.deviceContext){};

  ID3D11DeviceContext* deviceContext = nullptr;

  ID3D11DeviceContext* operator->() const { return deviceContext; };

  operator ID3D11DeviceContext*() const { return deviceContext; }
};

}  // namespace impl
}  // namespace cubit
