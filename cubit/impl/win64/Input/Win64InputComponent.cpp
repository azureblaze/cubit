#include "Win64InputComponent.h"

#include "Win64Input.h"

namespace cubit {
namespace impl {

boost::di::injector<Input&, Win64Input&> getWin64InputComponent() {
  return boost::di::make_injector(
      boost::di::bind<Input, Win64Input>().to<Win64Input>());
}

}  // namespace impl
}  // namespace cubit
