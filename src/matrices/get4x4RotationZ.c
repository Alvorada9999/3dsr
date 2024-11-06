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
#include <math.h>

struct Matrix4x4 get4x4RotationZ(float beta) {
  struct Matrix4x4 m = get4x4Identity();
  m.m[0][0] = cos(beta);
  m.m[1][0] = sin(beta);
  m.m[0][1] = -sin(beta);
  m.m[1][1] = cos(beta);
  return m;
}
