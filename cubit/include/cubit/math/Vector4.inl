#include <cubit/math/Matrix4.h>
#include <cubit/math/Vector4.h>

namespace cubit {
inline Vector4 Vector4::operator*(const Matrix4& m) {
  return Vector4(
      u[0] * m[0][0] + u[1] * m[1][0] + u[2] * m[2][0] + u[3] * m[3][0],
      u[0] * m[0][1] + u[1] * m[1][1] + u[2] * m[2][1] + u[3] * m[3][1],
      u[0] * m[0][2] + u[1] * m[1][2] + u[2] * m[2][2] + u[3] * m[3][2],
      u[0] * m[0][3] + u[1] * m[1][3] + u[2] * m[2][3] + u[3] * m[3][3]);
}

}  // namespace cubit
