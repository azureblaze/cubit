#pragma once

#include <boost/di.hpp>

struct ID3D11Device;
struct ID3D11DeviceContext;
namespace cubit {
namespace impl {

static auto DevicePtr = [] {};
static auto DeviceContextPtr = [] {};

struct Dx11Device {
  Dx11Device(ID3D11Device* device) : device(device) {}

  ID3D11Device* device = nullptr;

  ID3D11Device* operator->() const { return device; };

  operator ID3D11Device*() const { return device; }
};

struct Dx11DeviceContext {
  Dx11DeviceContext(ID3D11DeviceContext* deviceContext)
      : deviceContext(deviceContext) {}

  ID3D11DeviceContext* deviceContext = nullptr;

  ID3D11DeviceContext* operator->() const { return deviceContext; };

  operator ID3D11DeviceContext*() const { return deviceContext; }
};

}  // namespace impl
}  // namespace cubit
