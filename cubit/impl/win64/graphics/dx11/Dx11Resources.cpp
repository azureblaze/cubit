﻿#include "Dx11Resources.h"

#include <map>

#include <cubit/Inject/FactoryRegistry.h>

#include "Dx11Device.h"
#include "Dx11Material.h"
#include "Dx11Model.h"

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
  Dx11Resources* resources;
  Dx11Device device;
  Dx11DeviceContext deviceContext;
  Factory<Dx11Material, Dx11Resources*> materialFactory;

  ResourceHolder<string, Dx11Model> models;
  ResourceHolder<string, Dx11Material> materials;
  ResourceHolder<ShaderSpec, Dx11VertexShader> vertexShaders;
  ResourceHolder<ShaderSpec, Dx11PixelShader> pixelShaders;
  Factory<DebugAxis, Dx11Resources*> debugAxisFactory;

  unique_ptr<Dx11Model> loadModel(const std::string& name) {
    return unique_ptr(debugAxisFactory(resources));
  }

  unique_ptr<Dx11Material> loadMaterial(const std::string& name) {
    return materialFactory(resources);
  }

  Impl(
      Dx11Resources* resources,
      Dx11Device device,
      Dx11DeviceContext deviceContext,
      Dx11VertexShaderFactory vertexShaderFactory,
      Dx11PixelShaderFactory pixelShaderFactory,
      Factory<Dx11Material, Dx11Resources*> materialFactory,
      Factory<DebugAxis, Dx11Resources*> debugAxisFactory)
      : resources(resources),
        device(device),
        deviceContext(deviceContext),
        materialFactory(materialFactory),
        models(bind(&Impl::loadModel, this, _1)),
        materials(bind(&Impl::loadMaterial, this, _1)),
        vertexShaders(vertexShaderFactory),
        pixelShaders(pixelShaderFactory),
        debugAxisFactory(debugAxisFactory) {}
};

Dx11Resources::Dx11Resources(
    Dx11Device device,
    Dx11DeviceContext deviceContext,
    Dx11VertexShaderFactory vertexShaderFactory,
    Dx11PixelShaderFactory pixelShaderFactory,
    Factory<Dx11Material, Dx11Resources*> materialFactory,
    Factory<DebugAxis, Dx11Resources*> debugAxisFactory)
    : impl(make_unique<Impl>(
          this,
          device,
          deviceContext,
          vertexShaderFactory,
          pixelShaderFactory,
          materialFactory,
          debugAxisFactory)) {}

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
