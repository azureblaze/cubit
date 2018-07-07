#include <cubit/graphics/scene.h>

#include <map>
#include <memory>
#include <set>

#include <cubit/graphics/Camera.h>
#include <cubit/graphics/Instance.h>
#include <cubit/graphics/Material.h>
#include <cubit/graphics/Model.h>
#include <cubit/graphics/RenderTarget.h>

using namespace std;

namespace cubit {

struct Scene::Impl {
  Camera camera;

  set<unique_ptr<Instance>> instances;
};

struct ActiveModel {
  const Model* model;
  set<Instance*> instances;
};

struct ActiveMaterial {
  Material* model;
  set<const ActiveModel*> models;
};

Scene::Scene() : impl(make_unique<Impl>()) {}

Scene::~Scene() {}

Scene& Scene::setCamera(const Camera& camera) {
  impl->camera = camera;
  return *this;
}

const cubit::Camera& Scene::getCamera() const { return impl->camera; }

cubit::Instance* Scene::addInstance(const Model& model) {
  std::unique_ptr<Instance> instance = model.createInstance();
  Instance* pointer = instance.get();
  impl->instances.insert(move(instance));
  return pointer;
}

void Scene::render(RenderTarget& renderTarget) {
  renderTarget.bind();

  map<const Model*, ActiveModel> models;
  for (auto& instance : impl->instances) {
    const Model* model = instance->getModel();
    if (models.find(model) == models.end()) {
      models[model] = ActiveModel{model};
    }
    models[model].instances.insert(instance.get());
  }

  map<Material*, ActiveMaterial> materials;
  for (auto& activeModel : models) {
    const ActiveModel* model = &(activeModel.second);
    Material* material = model->model->getMaterial();
    if (materials.find(material) == materials.end()) {
      materials[material] = ActiveMaterial{material};
    }
    materials[material].models.insert(model);
  }

  for (auto material : materials) {
    material.first->begin(*this);

    for (auto model : material.second.models) {
      model->model->drawPrimitives(model->instances);
    }
    material.first->end();
  }
}

}  // namespace cubit
