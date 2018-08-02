#pragma once
#include <cubit/graphics/RenderTarget.h>

#include <fruit/fruit.h>

#include <functional>
#include <memory>

#include <cubit/inject/Factory.h>

#include "Dx11Device.h"
#include "Dx11Texture2D.h"

struct ID3D11RenderTargetView;

namespace cubit {
namespace impl {
class Dx11Texture2D;

class Dx11RenderTarget : public RenderTarget {
 private:
  friend class Dx11Renderer;

  Dx11DeviceContext deviceContext;
  ComPtr<ID3D11RenderTargetView> target;

  std::shared_ptr<Dx11Texture2D> texture;

  virtual void clear(Color color) override;

 public:
  INJECT(Dx11RenderTarget(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      ASSISTED(std::shared_ptr<Dx11Texture2D>) texture));
  ~Dx11RenderTarget();

  virtual void bind() override;
};

using Dx11RenderTargetFactory =
    Factory<Dx11RenderTarget, std::shared_ptr<Dx11Texture2D>>;

}  // namespace impl
}  // namespace cubit
