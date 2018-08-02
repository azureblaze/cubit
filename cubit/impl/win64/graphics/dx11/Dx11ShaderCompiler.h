#pragma once
#include <string_view>

#include <d3d11.h>

#include "ComPtr.h"

#undef max

namespace cubit {
namespace impl {
namespace Dx11ShaderCompiler {
ComPtr<ID3DBlob> compile(
    const std::string& filename,
    const std::string& entryPoint,
    const std::string& profile);
}  // namespace Dx11ShaderCompiler
}  // namespace impl
}  // namespace cubit
