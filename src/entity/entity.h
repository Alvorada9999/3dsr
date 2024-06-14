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

#ifndef _3DSR_ENTITY
#define _3DSR_ENTITY
#include "vector.h"
#include "stdint.h"

struct entity {
  struct vector3D *arrayOfVectors;
  struct vector2D *arrayOfVectorsProjections;
  uint32_t numberOfVectors;
};
#include "common.h"

void drawEntity(struct collorBuffer *collorBuffer, struct entity entity);
void scaleEntity(struct entity entity, float value);
void translateEntity(struct entity entity, float x, float y, float z);
void performPerspectiveProjectionOnEntity(struct entity entity);

#endif // !_3DSR_ENTITY
