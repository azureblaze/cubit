#pragma once

struct ID3D11Device;
struct ID3D11DeviceContext;
namespace cubit {
namespace impl {

struct Dx11Device {
  Dx11Device(ID3D11Device* device) : device(device) {}

  Dx11Device(Dx11Device& d) : device(d.device){};

  ID3D11Device* device = nullptr;

  ID3D11Device* operator->() const { return device; };

  operator ID3D11Device*() const { return device; }
};

struct Dx11DeviceContext {
  Dx11DeviceContext(ID3D11DeviceContext* device) : device(device) {}

  Dx11DeviceContext(Dx11DeviceContext& d) : device(d.device){};

  ID3D11DeviceContext* device = nullptr;

  ID3D11DeviceContext* operator->() const { return device; };

  operator ID3D11DeviceContext*() const { return device; }
};

}  // namespace impl
}  // namespace cubit
