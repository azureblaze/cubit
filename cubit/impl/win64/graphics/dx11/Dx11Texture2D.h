#pragma once
#include <cubit/graphics/Texture2D.h>

#include <wrl/client.h>

struct ID3D11Texture2D;
namespace cubit {
namespace impl {
class Dx11Texture2D : Texture2D {
 private:
  friend class Dx11Renderer;
  Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

 public:
  Dx11Texture2D() {}
  ~Dx11Texture2D();
};
}  // namespace impl
}  // namespace cubit
