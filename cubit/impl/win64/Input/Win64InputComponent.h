#pragma once

#include <fruit/fruit.h>

namespace cubit {
class Input;
namespace impl {
class Win64Input;
using Win64InputComponent = fruit::Component<Input, Win64Input>;
Win64InputComponent getWin64InputComponent();
}  // namespace impl
};  // namespace cubit
