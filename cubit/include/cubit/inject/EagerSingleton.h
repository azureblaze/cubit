#pragma once

#include <boost/di.hpp>

namespace cubit {

struct EagerSingleton {};

namespace impl {
template <
    class TDependency,
    class TInjector,
    std::enable_if_t<
        std::is_base_of<EagerSingleton, typename TDependency::expected>::value,
        int> = 0>
void create_singletons_eagerly_impl(
    const boost::di::aux::type<TDependency> &,
    const TInjector &injector) {
  injector.template create<std::shared_ptr<typename TDependency::expected>>();
}

template <
    class TDependency,
    class TInjector,
    std::enable_if_t<
        !std::is_base_of<EagerSingleton, typename TDependency::expected>::value,
        int> = 0>
void create_singletons_eagerly_impl(
    const boost::di::aux::type<TDependency> &,
    const TInjector &) {}

template <class... TDeps, class TInjector>
void create_singletons_eagerly(
    const boost::di::aux::type_list<TDeps...> &,
    const TInjector &injector) {
  [](...) {
  }((create_singletons_eagerly_impl(di::aux::type<TDeps>{}, injector), 0)...);
}
}  // namespace impl
template <class TInjector>
void InitializeEagerSingletons(const TInjector &injector) {
  impl::create_singletons_eagerly(typename TInjector::deps{}, injector);
}

}  // namespace cubit
