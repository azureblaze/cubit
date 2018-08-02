#pragma once
#include <cubit/config/config.h>

#include <map>
#include <memory>

#include <fruit/fruit.h>

namespace cubit {
namespace impl {
class ConstMapConfigEntry;

class ConstMapConfig : public cubit::Config {
 public:
  INJECT(ConstMapConfig());
  ~ConstMapConfig();
  virtual int getInt(std::string_view) const override;
  virtual float getFloat(std::string_view) const override;
  virtual std::string getString(std::string_view) const override;

 private:
  std::map<std::string, ConstMapConfigEntry*, std::less<>> entries;
};

}  // namespace impl
}  // namespace cubit
