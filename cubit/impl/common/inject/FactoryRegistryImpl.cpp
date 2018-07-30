#include "FactoryRegistryImpl.h"

#include <map>
#include <unordered_map>

using namespace std;

namespace cubit {
namespace impl {

struct FactoryRegistryImpl::Impl {
  unordered_map<type_index, map<string, unique_ptr<FactoryWrapperInterface>>>
      factories;
};

FactoryRegistryImpl::FactoryRegistryImpl() : impl(make_unique<Impl>()) {}

FactoryRegistryImpl::~FactoryRegistryImpl() {}

void FactoryRegistryImpl::registerTypeid(
    std::type_index type,
    const std::string& key,
    std::unique_ptr<impl::FactoryWrapperInterface>&& factory) {
  impl->factories[type][key] = move(factory);
}

cubit::impl::FactoryWrapperInterface* FactoryRegistryImpl::getFactory(
    std::type_index type,
    const std::string key) {
  if (impl->factories.find(type) == impl->factories.end()) {
    return nullptr;
  }
  auto& map = impl->factories[type];
  if (map.find(key) == map.end()) {
    return nullptr;
  }
  return map[key].get();
}
}  // namespace impl
}  // namespace cubit
