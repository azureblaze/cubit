#include <cubit/cubit.h>

#include "win64/core/Win64CoreComponent.h"

namespace cubit {
	std::shared_ptr<Application> createWin64Application(void* instance, std::string_view commandLine) {
		return cubit::impl::getWin64CoreInjector(instance, commandLine).create<std::shared_ptr<Application>>();
	}
}