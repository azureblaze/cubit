#pragma once
namespace cubit {
namespace impl {
class RenderEngine {
 public:
  virtual ~RenderEngine() = default;

  virtual void present() = 0;
};
}  // namespace impl
}  // namespace cubit
