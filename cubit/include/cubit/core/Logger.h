#pragma once
#include <sstream>
#include <string_view>
namespace cubit {
class Logger {
 public:
  virtual ~Logger() = default;
  virtual void log(std::string_view str) = 0;

  class Stream {
    friend class Logger;
    Logger& logger;
    Stream(Logger& logger) : logger(logger) {}

   public:
    Stream(Stream&& m) = default;
    Stream(Stream& m) = default;

    template <class T>
    Stream& operator<<(const T& in) {
      std::stringstream stringStream;
      stringStream << in;
      logger.log(stringStream.str());
      return *this;
    }
  };

  Stream stream() { return std::move(Stream(*this)); }
};
}  // namespace cubit
