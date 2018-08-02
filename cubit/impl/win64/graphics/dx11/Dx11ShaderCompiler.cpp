#include "Dx11ShaderCompiler.h"

#include <fstream>
#include <sstream>

#include <D3Dcompiler.h>
#include <d3d11.h>

#include "ComPtr.h"
#include "DxResult.h"

using namespace std;

namespace cubit {
namespace impl {

namespace Dx11ShaderCompiler {

const static string utf8Bom = "\xEF\xBB\xBF";

static string fileToString(const string& filename) {
  ifstream fin;
  fin.open(filename, ifstream::in);
  stringstream buffer;
  buffer << fin.rdbuf();
  string data = buffer.str();
  if (data.size() >= utf8Bom.size() &&
      data.substr(0, utf8Bom.size()) == utf8Bom) {
    return data.substr(utf8Bom.size());
  }
  return data;
}

ComPtr<ID3DBlob> compile(
    const string& filename,
    const string& entryPoint,
    const string& profile) {
  ComPtr<ID3DBlob> blob;
  ComPtr<ID3DBlob> errors;

  string file = fileToString(filename);

  HRESULT result = D3DCompile(
      file.data(),
      file.size(),
      filename.c_str(),
      NULL,
      NULL,
      entryPoint.c_str(),
      profile.c_str(),
      D3DCOMPILE_DEBUG,
      0,
      blob.GetAddressOf(),
      errors.GetAddressOf());
  checkResult(result, errors.Get());
  return blob;
}
}  // namespace Dx11ShaderCompiler
}  // namespace impl
}  // namespace cubit
