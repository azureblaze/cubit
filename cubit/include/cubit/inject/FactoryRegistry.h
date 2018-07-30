#pragma once

#include <string>
#include <typeindex>

#include "Factory.h"

namespace cubit {
namespace impl {
struct FactoryWrapperInterface {
  virtual ~FactoryWrapperInterface(){};

  virtual void* get() = 0;
};

template <class T>
struct FactoryWrapper : public FactoryWrapperInterface {
  Factory<T> factory;

  FactoryWrapper(Factory<T> factory) : factory(factory) {}

  virtual void* get() override { return &factory; }
};
}  // namespace impl
class FactoryRegistry {
 public:
  virtual ~FactoryRegistry(){};

  virtual void registerTypeid(
      std::type_index type,
      const std::string& key,
      std::unique_ptr<impl::FactoryWrapperInterface>&& factory) = 0;

  template <class T>
  void registerFactory(const std::string& key, Factory<T> factory) {
    registerTypeid(
        typeid(T), key, std::make_unique<impl::FactoryWrapper<T>>(factory));
  }

  virtual impl::FactoryWrapperInterface* getFactory(
      std::type_index type,
      const std::string key) = 0;

  template <class T>
  Factory<T>* get(const std::string& key) {
    impl::FactoryWrapperInterface* factory = getFactory(typeid(T), key);
    if (factory == nullptr) {
      return nullptr;
    }
    return reinterpret_cast<Factory<T>*>(factory->get());
  }
};
}  // namespace cubit
