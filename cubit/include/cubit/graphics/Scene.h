#pragma once

#include <memory>

namespace cubit {

class RenderTarget;
class Camera;
class Instance;
class Model;

class Scene {
  struct Impl;
  std::unique_ptr<Impl> impl;

 public:
  Scene();
  ~Scene();

  Scene& setCamera(const Camera& camera);
  const Camera& getCamera() const;

  Instance* addInstance(const Model& model);

  void render(RenderTarget& renderTarget);
};
}  // namespace cubit
