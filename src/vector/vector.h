// This file is part of 3dsr.
// Copyright (C) 2024 Kenedy Henrique Bueno Silva

// donttrust is free software: you can redistribute it and/or modify
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

typedef struct {
  float x;
  float y;
} vector2D;

typedef struct {
  float x;
  float y;
  float z;
} vector3D;

void scale3DVector(vector3D *vector3D, float x, float y, float z);
void translate3DVector(vector3D *vector3D, uint32_t x, uint32_t y, uint32_t z);

#endif // !_3DSR_VECTOR
