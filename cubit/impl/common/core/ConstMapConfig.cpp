#include <cassert>
#include "ConstMapConfig.h"
using namespace std;

namespace cubit {
namespace impl {
class ConstMapConfigEntry {
 public:
  virtual ~ConstMapConfigEntry(){};

  virtual int getInt() {
    assert(false);
    return 0;
  }
  virtual int getFloat() {
    assert(false);
    return 0;
  };
  virtual string getString() {
    assert(false);
    return "";
  }
};

class IntEntry : public ConstMapConfigEntry {
 public:
  IntEntry(int value) : value(value) {}

  virtual int getInt() override { return value; }

 private:
  int value;
};

class FloatEntry : public ConstMapConfigEntry {
 public:
  FloatEntry(float value) : value(value) {}

  virtual int getFloat() override { return value; }

 private:
  float value;
};

class StringEntry : public ConstMapConfigEntry {
 public:
  StringEntry(string_view value) : value(value) {}

  virtual string getString() { return value; }

 private:
  string value;
};

pair<string, ConstMapConfigEntry*> Int(string_view key, int value) {
  return make_pair(string(key), new IntEntry(value));
}

pair<string, ConstMapConfigEntry*> Float(string_view key, float value) {
  return make_pair(string(key), new FloatEntry(value));
}
pair<string, ConstMapConfigEntry*> String(string_view key, string_view value) {
  return make_pair(string(key), new StringEntry(value));
}

ConstMapConfig::ConstMapConfig()
    : entries{Int("default_window_width", 1920),
              Int("default_window_height", 1080),
              Float("max_fps", 60.0f),
              Int("frame_update_metrics_period", 60)} {}

ConstMapConfig::~ConstMapConfig() {
  for (auto entry : entries) {
    delete entry.second;
  }
}
int ConstMapConfig::getInt(std::string_view key) const {
  return entries.find(key)->second->getInt();
}
float ConstMapConfig::getFloat(std::string_view key) const {
  return entries.find(key)->second->getFloat();
}
std::string ConstMapConfig::getString(std::string_view key) const {
  return entries.find(key)->second->getString();
}
}  // namespace impl
}  // namespace cubit
