#pragma once

#include <string>
#include <typeindex>

#include <fruit/fruit.h>

#include "Factory.h"
#include "FactoryEntry.h"

namespace cubit {
class Model;
class Resources;
namespace impl {
struct FactoryWrapperInterface {
  virtual ~FactoryWrapperInterface(){};

  virtual void* get() = 0;
};

template <class T, class... Args>
struct FactoryWrapper : public FactoryWrapperInterface {
  Factory<T, Args...> factory;

  FactoryWrapper(Factory<T, Args...> factory) : factory(factory) {}

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

  template <class T, class... Args>
  void registerFactory(const std::string& key, Factory<T, Args...> factory) {
    registerTypeid(
        typeid(T),
        key,
        std::make_unique<impl::FactoryWrapper<T, Args...>>(factory));
  }

  template <class... Args>
  void registerFactories(fruit::Injector<Args...>& injector) {
    for (auto& entry :
         injector.getMultibindings<FactoryEntry<Model, Resources*>>()) {
      registerFactory<Model, Resources*>(entry->key(), entry->value());
    }
  }

  virtual impl::FactoryWrapperInterface* getFactory(
      std::type_index type,
      const std::string key) = 0;

  template <class T, class... Args>
  Factory<T, Args...>* get(const std::string& key) {
    impl::FactoryWrapperInterface* factory = getFactory(typeid(T), key);
    if (factory == nullptr) {
      return nullptr;
    }
    return reinterpret_cast<Factory<T, Args...>*>(factory->get());
  }
};
}  // namespace cubit
