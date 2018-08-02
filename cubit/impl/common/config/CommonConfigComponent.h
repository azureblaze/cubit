#pragma once

#include <fruit/fruit.h>

namespace cubit {
class Config;
namespace impl {
fruit::Component<Config> getCommonConfigComponent();
}  // namespace impl
}  // namespace cubit
