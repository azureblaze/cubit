#include "Win64CoreComponent.h"

#include <memory>

#include <cubit/core/FrameUpdateMetrics.h>

#include "Win64Application.h"
#include "Win64Window.h"
#include "common/config/CommonConfigComponent.h"
#include "common/core/CommonCoreComponent.h"
#include "win64/graphics/dx11/dx11GraphicComponent.h"
#include "win64/input/Win64InputComponent.h"
#include "win64/os/Win64OsComponent.h"

namespace di = boost::di;
using namespace std;

namespace cubit {
namespace impl {
di::injector<Application&> getWin64CoreInjector(
    intptr_t applicationInstance,
    string_view commandLineArgs) {
  return di::make_injector(
      getCommonConfigComponent(),
      getCommonCoreInjector(),
      getDx11GraphicsComponent(),
      getWin64OsComponent(),
      getWin64InputComponent(),
      di::bind<Application>().to<Win64Application>(),
      di::bind<Win64Application::Spec>().to(
          Win64Application::Spec{applicationInstance, commandLineArgs}),
      di::bind<Win64WindowFactory>().to(
          di::extension::assisted_injection<Win64Window>{}));
}
}  // namespace impl
}  // namespace cubit
