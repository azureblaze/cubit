#pragma once
#include <cubit/core/application.h>
#include <boost/di.hpp>
#include <string_view>
namespace cubit {
namespace impl {

class Win64Application : public Application {
 public:
  struct Spec {
    void* applicationInstance;
    std::string_view commandLineArgs;
  };

  Win64Application(const Spec& spec);
  int start() override;

 private:
  const Spec spec;
};
}  // namespace impl
}  // namespace cubit