#pragma once
#include "Vector4.h"

#include <emmintrin.h>
#include <cmath>
#include <cstring>

namespace cubit {
class alignas(16) Matrix4 {
  Vector4 r[4];

 public:
  Matrix4() {}
  Matrix4(const Matrix4& other) { *this = other; }
  Matrix4(
      const Vector4& v0,
      const Vector4& v1,
      const Vector4& v2,
      const Vector4& v3) {
    r[0] = v0;
    r[1] = v1;
    r[2] = v2;
    r[3] = v3;
  }

  Matrix4& operator=(const Matrix4& other) {
    if (this == &other) {
      return *this;
    }
    for (int i = 0; i < 4; i++) {
      r[i] = other[i];
    }
  }

  Vector4& operator[](size_t index) { return r[index]; }
  const Vector4& operator[](size_t index) const { return r[index]; }

  Matrix4 operator*(float k) const {
    return Matrix4(r[0] * k, r[1] * k, r[2] * k, r[3] * k);
  }

  Matrix4 operator*(const Matrix4& o) const {
    Matrix4 c;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          c[i][j] += r[i][k] * o[k][j];
        }
      }
    }
    return c;
  }

  Matrix4 transpose() const {
    Matrix4 t;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        t[i][j] = r[j][i];
      }
    }
    return t;
  }

  const static Matrix4& identity() {
    static Matrix4 m{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    return m;
  }

  static Matrix4 translate(const Vector3& t) {
    return {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, Vector4(t, 1)};
  }

  static Matrix4 rotateX(float phi) {
    using namespace std;
    return {{1, 0, 0, 0},
            {0, cosf(phi), sinf(phi), 0},
            {0, -sinf(phi), cosf(phi), 0},
            {0, 0, 0, 1}};
  }
  static Matrix4 rotateY(float theta) {
    using namespace std;
    return {{cosf(theta), 0, -sinf(theta), 0},
            {0, 1, 0, 0},
            {sinf(theta), 0, cosf(theta), 0},
            {0, 0, 0, 1}};
  }
  static Matrix4 rotateZ(float gamma) {
    return {{cosf(gamma), sinf(gamma), 0, 0},
            {-sinf(gamma), cosf(gamma), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}};
  }

  static Matrix4 scale(const Vector3& s) {
    return {{s[0], 0, 0, 0}, {0, s[1], 0, 0}, {0, 0, s[2], 0}, {0, 0, 0, 1}};
  }
};

inline Matrix4 operator*(float scale, const Matrix4& matrix) {
  return matrix * scale;
}

}  // namespace cubit
