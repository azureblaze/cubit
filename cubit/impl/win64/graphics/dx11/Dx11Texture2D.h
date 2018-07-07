#pragma once
#include <cubit/graphics/Texture2D.h>

#include <wrl/client.h>

struct ID3D11Texture2D;
namespace cubit {
namespace impl {
class Dx11Texture2D : Texture2D {
 private:
  friend class Dx11Renderer;
  friend class Dx11RenderTarget;
  Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

  int width;
  int height;

 public:
  Dx11Texture2D(int width, int height);
  ~Dx11Texture2D();

  virtual int getWidth() override;

  virtual int getHeight() override;
};
}  // namespace impl
}  // namespace cubit
