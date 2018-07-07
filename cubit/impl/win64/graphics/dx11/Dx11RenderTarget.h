#pragma once
#include <cubit/graphics/RenderTarget.h>

#include <boost/di.hpp>
#include <boost/di/extension/injections/assisted_injection.hpp>

#include <functional>
#include <memory>

#include <wrl/client.h>

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
  Microsoft::WRL::ComPtr<ID3D11RenderTargetView> target;

  std::shared_ptr<Dx11Texture2D> texture;

  virtual void clear(Color color) override;

 public:
  BOOST_DI_INJECT(
      Dx11RenderTarget,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      (named = boost::di::extension::assisted)
          std::shared_ptr<Dx11Texture2D> texture);
  ~Dx11RenderTarget();

  virtual void bind() override;
};

using Dx11RenderTargetFactory = std::function<std::unique_ptr<Dx11RenderTarget>(
    std::shared_ptr<Dx11Texture2D>)>;

}  // namespace impl
}  // namespace cubit
