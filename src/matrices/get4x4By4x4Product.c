// This file is part of 3dsr.
// Copyright (C) 2024 Kenedy Henrique Bueno Silva

// 3dsr is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "matrices.h"
#include <stdint.h>

struct Matrix4x4 get4x4By4x4Product(struct Matrix4x4 *a, struct Matrix4x4 *b) {
  struct Matrix4x4 m;
  for (uint8_t i = 0; i < 4; i++) {
    for (uint8_t j = 0; j < 4; j++) {
      m.m[i][j] = (*a).m[i][0]*(*b).m[0][j] + (*a).m[i][1]*(*b).m[1][j] + (*a).m[i][2]*(*b).m[2][j] + (*a).m[i][3]*(*b).m[3][j];
    }
  }
  return m;
}
