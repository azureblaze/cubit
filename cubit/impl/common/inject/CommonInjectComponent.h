#pragma once
#include <memory>

#include <boost/di.hpp>

namespace cubit {

class FactoryRegistry;
boost::di::injector<std::shared_ptr<FactoryRegistry>>
getCommonInjectComponent();
}  // namespace cubit
