#pragma once

#include <boost/di.hpp>

namespace cubit {
class Input;
namespace impl {
class Win64Input;
boost::di::injector<Input&, Win64Input&> getWin64InputComponent();
}  // namespace impl
};  // namespace cubit
