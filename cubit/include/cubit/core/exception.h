#pragma once
#include <string.h>
#include <string_view>
namespace cubit {

class Exception {
  std::string message;

 public:
  Exception() {}
  Exception(std::string_view message) : message(message) {}
  ~Exception() = default;

  std::string_view getMessage() { return message; }
};

}  // namespace cubit
