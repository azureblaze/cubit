#pragma once
#include <functional>
#include <memory>

namespace cubit {

template <class T, class... Param>
using Factory = std::function<std::unique_ptr<T>(Param...)>;
}
