#include "Dx11InternalComponent.h"

#include <string>

#include "Dx11Device.h"
#include "Dx11Material.h"
#include "Dx11PixelShader.h"
#include "Dx11RenderTarget.h"
#include "Dx11Resources.h"
#include "Dx11Texture2D.h"
#include "Dx11VertexBuffer.h"
#include "Dx11VertexShader.h"

#include "models/DebugAxis.h"

using namespace std;

namespace cubit {
namespace impl {

Dx11InternalComponent getDx11InternalComponent(
    Dx11Device* device,
    Dx11DeviceContext* deviceContext) {
  return fruit::createComponent().bindInstance(*device).bindInstance(
      *deviceContext);
}
}  // namespace impl
}  // namespace cubit
