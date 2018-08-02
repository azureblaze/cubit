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
Win64CoreComponent getWin64CoreInjector() {
  return fruit::createComponent()
      .registerFactory<std::unique_ptr<Application>(
          fruit::Assisted<intptr_t>,
          fruit::Assisted<string_view>,
          Factory<Win64Application, const Win64Application::Spec&>)>(
          [](intptr_t applicationInstance,
             string_view commandLineArgs,
             Factory<Win64Application, const Win64Application::Spec&>
                 applicationFactory) {
            return unique_ptr<Application>(applicationFactory(
                Win64Application::Spec{applicationInstance, commandLineArgs}));
          });
}
}  // namespace impl
}  // namespace cubit
