#include "Win64CoreComponent.h"

#include <memory>

#include <cubit/config/config.h>
#include <cubit/core/FrameUpdateMetrics.h>
#include <cubit/os/Logger.h>

#include "Win64Application.h"
#include "Win64Window.h"

#include "win64/input/Win64Input.h"

using namespace std;

namespace cubit {
namespace impl {
Win64CoreComponent getWin64CoreInjector(
    intptr_t applicationInstance,
    string_view commandLineArgs) {
  static const Win64Application::Spec spec{applicationInstance,
                                           commandLineArgs};
  return fruit::createComponent()
      .bindInstance(spec)
      .bind<Application, Win64Application>();
}
}  // namespace impl
}  // namespace cubit
