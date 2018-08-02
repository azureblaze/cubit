#pragma once
#include <fruit/fruit.h>

namespace cubit {
namespace impl {
template <class... FormalArgs, class... Args>
fruit::Injector<Args...> InjectorForHelper(
    fruit::Component<Args...> (*)(FormalArgs...)) {}
}  // namespace impl
}  // namespace cubit

#define INJECTOR_FOR(component) decltype(InjectorForHelper(component))
