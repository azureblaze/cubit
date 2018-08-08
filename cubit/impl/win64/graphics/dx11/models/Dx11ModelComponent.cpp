#include "Dx11ModelComponent.h"

#include <fruit/fruit.h>

#include <cubit/Inject/FactoryEntry.h>

#include "../Dx11Resources.h"

#include "DebugAxis.h"

namespace cubit {
class Resources;
namespace impl {

class DebugAxisEntry : public FactoryEntry<Model, Resources*> {
  Factory<DebugAxis, Dx11Resources*> factory;

 public:
  INJECT(DebugAxisEntry(Factory<DebugAxis, Dx11Resources*> factory))
      : factory(factory){};
  virtual const std::string key() const override { return "debug:axis"; }

  virtual Factory<Model, Resources*> value() override {
    return [&](Resources* resources) {
      return std::unique_ptr<Model>(
          factory(dynamic_cast<Dx11Resources*>(resources)));
    };
  }
};

Dx11ModelComponent getDx11ModelComponent() {
  return fruit::createComponent()
      .addMultibinding<FactoryEntry<Model, Resources*>, DebugAxisEntry>();
}

}  // namespace impl
}  // namespace cubit
