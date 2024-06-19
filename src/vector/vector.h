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

#ifndef _3DSR_VECTOR
#define _3DSR_VECTOR

#include "stdint.h"

struct vector2D {
  float x;
  float y;
};

struct vector3D {
  float x;
  float y;
  float z;
};

void rotateXVector3D(struct vector3D *vector3D, float beta);
void rotateYVector3D(struct vector3D *vector3D, float beta);
void rotateZVector3D(struct vector3D *vector3D, float beta);

#endif // !_3DSR_VECTOR

