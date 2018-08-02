#pragma once
#include <string_view>

#include <wrl/client.h>

#include <d3d11.h>

#undef max

namespace cubit {
namespace impl {
namespace Dx11ShaderCompiler {
Microsoft::WRL::ComPtr<ID3DBlob> compile(
    const std::string& filename,
    const std::string& entryPoint,
    const std::string& profile);
}  // namespace Dx11ShaderCompiler
}  // namespace impl
}  // namespace cubit
