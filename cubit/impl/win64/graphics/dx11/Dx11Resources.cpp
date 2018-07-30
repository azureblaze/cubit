#include "Dx11Resources.h"

#include <map>

#include <cubit/Inject/FactoryRegistry.h>

#include "Dx11Device.h"
#include "Dx11Material.h"
#include "Dx11Model.h"

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

  std::shared_ptr<FactoryRegistry> factoryRegistry;

  ResourceHolder<string, Dx11Model> models;
  ResourceHolder<string, Dx11Material> materials;
  ResourceHolder<ShaderSpec, Dx11VertexShader> vertexShaders;
  ResourceHolder<ShaderSpec, Dx11PixelShader> pixelShaders;

  unique_ptr<Dx11Model> loadModel(const std::string& name) {
    auto factory = factoryRegistry->get<Dx11Model>(name);
    return (*factory)();
  }

  Impl(
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      std::shared_ptr<FactoryRegistry> factoryRegistry,
      Dx11VertexShaderFactory vertexShaderFactory,
      Dx11PixelShaderFactory pixelShaderFactory,
      Dx11MaterialFactory materialFactory)
      : device(device),
        deviceContext(deviceContext),
        factoryRegistry(factoryRegistry),
        materialFactory(materialFactory),
        models(bind(&Impl::loadModel, this, _1)),
        materials(bind(this->materialFactory)),
        vertexShaders(vertexShaderFactory),
        pixelShaders(pixelShaderFactory) {}
};

Dx11Resources::Dx11Resources(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    std::shared_ptr<FactoryRegistry> factoryRegistry,
    Dx11VertexShaderFactory vertexShaderFactory,
    Dx11PixelShaderFactory pixelShaderFactory,
    Dx11MaterialFactory materialFactory)
    : impl(make_unique<Impl>(
          device,
          deviceContext,
          factoryRegistry,
          vertexShaderFactory,
          pixelShaderFactory,
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
