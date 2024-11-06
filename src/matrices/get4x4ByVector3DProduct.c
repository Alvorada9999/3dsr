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

struct vector3D get4x4ByVector3DProduct(struct Matrix4x4 *a, struct vector3D *b) {
  struct vector3D v;
  v.x = (*a).m[0][0]*b->x + (*a).m[0][1]*b->y + (*a).m[0][2]*b->z + (*a).m[0][3]*b->w;
  v.y = (*a).m[1][0]*b->x + (*a).m[1][1]*b->y + (*a).m[1][2]*b->z + (*a).m[1][3]*b->w;
  v.z = (*a).m[2][0]*b->x + (*a).m[2][1]*b->y + (*a).m[2][2]*b->z + (*a).m[2][3]*b->w;
  v.w = (*a).m[3][0]*b->x + (*a).m[3][1]*b->y + (*a).m[3][2]*b->z + (*a).m[3][3]*b->w;
  return v;
}
