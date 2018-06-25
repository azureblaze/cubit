#pragma once

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

namespace cubit {
namespace impl {
void checkResult(int result);
void checkResult(int result, ID3DBlob* blob);
}  // namespace impl
}  // namespace cubit
