#include "Dx11Resources.h"

#include <map>

#include "Dx11Device.h"
#include "models/DebugAxis.h"

using namespace std;

namespace cubit {
namespace impl {

struct Dx11Resources::Impl {
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  DebugAxisFactory debugAxisFactory;

  std::map<string, unique_ptr<Model>> models;

  Impl(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      DebugAxisFactory debugAxisFactory)
      : device(device),
        deviceContext(deviceContext),
        debugAxisFactory(debugAxisFactory) {}

  void loadModel(const std::string& name) {
    if (name == "debug:axis") {
      models[name] = debugAxisFactory();
    }
  }
};

Dx11Resources::Dx11Resources(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    DebugAxisFactory debugAxisFactory)
    : impl(make_unique<Impl>(device, deviceContext, debugAxisFactory)) {}

Dx11Resources::~Dx11Resources() {}

const cubit::Model* Dx11Resources::getModel(const std::string& name) {
  auto& models = impl->models;
  if (models.find(name) == models.end()) {
    impl->loadModel(name);
  }
  return models[name].get();
}

}  // namespace impl
}  // namespace cubit
