#pragma once
#include <string>
#include <string_view>
namespace cubit {
namespace impl {
namespace Win64Util {
std::wstring utf8ToWchar(std::string_view utf8);
}
}  // namespace impl
}  // namespace cubit