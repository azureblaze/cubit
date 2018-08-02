#include "Win64InputComponent.h"

#include "Win64Input.h"

namespace cubit {
namespace impl {

Win64InputComponent getWin64InputComponent() {
  return fruit::createComponent().bind<Input, Win64Input>();
}

}  // namespace impl
}  // namespace cubit
