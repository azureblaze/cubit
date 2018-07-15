#include "Dx11Resources.h"

#include <map>

#include "Dx11Device.h"
#include "Dx11Material.h"
#include "models/DebugAxis.h"

using namespace std;
using namespace std::placeholders;

namespace cubit {
namespace impl {

template <class KEY, class R>
class ResourceHolder {
 public:
  using ResourceCreator = function<unique_ptr<R>(const KEY&)>;

 private:
  ResourceCreator resourceCreator;
  std::map<KEY, unique_ptr<R>> resources;

 public:
  ResourceHolder(ResourceCreator resourceCreator)
      : resourceCreator(resourceCreator) {}

  R* get(const KEY& key) {
    if (resources.find(key) == resources.end()) {
      resources[key] = move(resourceCreator(key));
    }
    return resources[key].get();
  }
};

struct Dx11Resources::Impl {
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  Dx11MaterialFactory materialFactory;

  DebugAxisFactory debugAxisFactory;

  ResourceHolder<string, Dx11Model> models;
  ResourceHolder<string, Dx11Material> materials;
  ResourceHolder<ShaderSpec, Dx11VertexShader> vertexShaders;
  ResourceHolder<ShaderSpec, Dx11PixelShader> pixelShaders;

  unique_ptr<Dx11Model> loadModel(const std::string& name) {
    if (name == "debug:axis") {
      return debugAxisFactory();
    }
  }

  Impl(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      Dx11VertexShaderFactory vertexShaderFactory,
      Dx11PixelShaderFactory pixelShaderFactory,
      DebugAxisFactory debugAxisFactory,
      Dx11MaterialFactory materialFactory)
      : device(device),
        deviceContext(deviceContext),
        debugAxisFactory(debugAxisFactory),
        materialFactory(materialFactory),
        models(bind(&Impl::loadModel, this, _1)),
        materials(bind(this->materialFactory)),
        vertexShaders(vertexShaderFactory),
        pixelShaders(pixelShaderFactory) {}
};

Dx11Resources::Dx11Resources(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    Dx11VertexShaderFactory vertexShaderFactory,
    Dx11PixelShaderFactory pixelShaderFactory,
    Dx11MaterialFactory materialFactory,
    DebugAxisFactory debugAxisFactory)
    : impl(make_unique<Impl>(
          device,
          deviceContext,
          vertexShaderFactory,
          pixelShaderFactory,
          debugAxisFactory,
          materialFactory)) {}

Dx11Resources::~Dx11Resources() {}

const cubit::Model* Dx11Resources::getModel(const std::string& name) {
  return impl->models.get(name);
}

const cubit::Material* Dx11Resources::getMaterial(const std::string& name) {
  return impl->materials.get(name);
}

const cubit::VertexShader* Dx11Resources::getVertexShader(
    const ShaderSpec& spec) {
  return impl->vertexShaders.get(spec);
  ;
}
const cubit::PixelShader* Dx11Resources::getPixelShader(
    const ShaderSpec& spec) {
  return impl->pixelShaders.get(spec);
}

}  // namespace impl
}  // namespace cubit
