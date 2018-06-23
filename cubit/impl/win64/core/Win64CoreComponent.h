#pragma once
#include <cubit/core/application.h>
#include <boost/di.hpp>
#include <string_view>

namespace cubit {
class Logger;
namespace impl {
boost::di::injector<Application&> getWin64CoreInjector(
    intptr_t applicationInstance,
    std::string_view commandLineArgs);
}
}  // namespace cubit
