#pragma once
#include <cubit/core/application.h>
#include <boost/di.hpp>
#include <string_view>

namespace cubit {
namespace impl {
const boost::di::injector<std::shared_ptr<Application>> getWin64CoreInjector(
    intptr_t applicationInstance,
    std::string_view commandLineArgs);
}
}  // namespace cubit
