#pragma once
#include <string>
#include <string_view>

namespace cubit {
class Config {
 public:
  virtual ~Config() = default;

 protected:
  virtual int getInt(std::string_view key) const = 0;
  virtual float getFloat(std::string_view key) const = 0;
  virtual std::string getString(std::string_view key) const = 0;

 public:
  template <class T>
  T get(std::string_view key) const = delete;

  template <>
  int get<int>(std::string_view key) const {
    return getInt(key);
  }

  template <>
  float get<float>(std::string_view key) const {
    return getFloat(key);
  }

  template <>
  std::string get<std::string>(std::string_view key) const {
    return getString(key);
  }
};
}  // namespace cubit
