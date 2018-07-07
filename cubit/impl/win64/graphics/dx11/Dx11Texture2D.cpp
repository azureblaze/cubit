#include "Dx11Texture2d.h"

#include <d3d11.h>

namespace cubit {
namespace impl {

Dx11Texture2D::Dx11Texture2D(int width, int height)
    : width(width), height(height) {}

Dx11Texture2D::~Dx11Texture2D() {}

int Dx11Texture2D::getWidth() { return width; }

int Dx11Texture2D::getHeight() { return height; }

}  // namespace impl
}  // namespace cubit
