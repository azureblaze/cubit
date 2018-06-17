#pragma once
namespace cubit {
class Application {
 public:
  virtual ~Application() = default;
  virtual int start() = 0;
};
}  // namespace cubit