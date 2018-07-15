#pragma once

#include <string>

namespace cubit {
class Model;
class Material;
class VertexShader;
class PixelShader;
struct ShaderSpec;

class Resources {
 public:
  virtual const Model* getModel(const std::string& name) = 0;
  virtual const Material* getMaterial(const std::string& name) = 0;
  virtual const VertexShader* getVertexShader(const ShaderSpec& spec) = 0;
  virtual const PixelShader* getPixelShader(const ShaderSpec& spec) = 0;
};
}  // namespace cubit
