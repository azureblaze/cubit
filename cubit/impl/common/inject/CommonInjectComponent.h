#pragma once

#include <fruit/fruit.h>

namespace cubit {
class FactoryRegistry;
namespace impl {
using CommonInjectComponent = fruit::Component<FactoryRegistry>;

CommonInjectComponent getCommonInjectComponent();
}  // namespace impl
}  // namespace cubit
