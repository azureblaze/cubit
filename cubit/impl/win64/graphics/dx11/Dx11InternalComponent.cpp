#include "Dx11InternalComponent.h"

#include <string>

#include <cubit/inject/FactoryRegistry.h>

#include "Dx11Device.h"
#include "Dx11Material.h"
#include "Dx11PixelShader.h"
#include "Dx11RenderTarget.h"
#include "Dx11Resources.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"

#include "win64/graphics/dx11/models/Dx11ModelComponent.h"

using namespace std;

namespace cubit {
namespace impl {

Dx11InternalComponent getDx11InternalComponent() {
  return fruit::createComponent().install(getDx11ModelComponent);
}
}  // namespace impl
}  // namespace cubit
