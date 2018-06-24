#include "Dx11Texture2d.h"

#include <d3d11.h>

namespace cubit {
namespace impl {

Dx11Texture2D::~Dx11Texture2D() { texture->Release(); }
}  // namespace impl
}  // namespace cubit
