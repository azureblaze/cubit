#pragma once
#include <cubit/Inject/FactoryRegistry.h>

#include <memory>

namespace cubit {
namespace impl {

class FactoryRegistryImpl : public FactoryRegistry {
  struct Impl;
  std::unique_ptr<Impl> impl;

 public:
  FactoryRegistryImpl();
  ;
  ~FactoryRegistryImpl();

  virtual void registerTypeid(
      std::type_index type,
      const std::string& key,
      std::unique_ptr<impl::FactoryWrapperInterface>&& factory) override;

  virtual impl::FactoryWrapperInterface* getFactory(
      std::type_index type,
      const std::string key) override;
};
}  // namespace impl
}  // namespace cubit
