#pragma once
#include <boost/di.hpp>
namespace cubit {
class Config;
namespace impl {
boost::di::injector<Config&> getCommonConfigComponent();
}  // namespace impl
}  // namespace cubit
