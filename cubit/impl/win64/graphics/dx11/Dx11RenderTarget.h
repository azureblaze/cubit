#pragma once
#include <cubit/graphics/RenderTarget.h>

#include <wrl/client.h>

struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

namespace cubit {
namespace impl {
class Dx11RenderTarget : public RenderTarget {
 private:
  friend class Dx11Renderer;

  ID3D11DeviceContext *deviceContext;
  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;

  virtual void clear(Color color) override;

 public:
  Dx11RenderTarget(ID3D11DeviceContext *deviceContext)
      : deviceContext(deviceContext){};
  ~Dx11RenderTarget();
};
}  // namespace impl
}  // namespace cubit
