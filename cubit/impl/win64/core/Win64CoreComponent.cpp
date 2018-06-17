#include <memory>
#include "Win64Application.h"
#include "Win64CoreComponent.h"

namespace di = boost::di;
using namespace std;

namespace cubit {
namespace impl {
const di::injector<std::shared_ptr<Application>> getWin64CoreInjector(
    void* applicationInstance,
    string_view commandLineArgs) {
  return di::make_injector(
      di::bind<Application>().to<Win64Application>(),
      di::bind<Win64Application::Spec>().to(
          Win64Application::Spec{applicationInstance, commandLineArgs}));
}
}  // namespace impl
}  // namespace cubit