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

#ifndef _3DSR_ENTITY
#define _3DSR_ENTITY
#include "vector.h"
#include "stdint.h"

struct triangle {
  uint32_t a;
  uint32_t b;
  uint32_t c;
};

struct entity {
  struct vector3D *vectors;
  uint32_t vectorsLength;
  struct triangle *triangles;
  uint32_t trianglesLength;
  float currentXTranslation;
  float currentYTranslation;
  float currentZTranslation;
};
#include "common.h"

void performPerspectiveProjectionOnEntity(struct collorBuffer *collorBuffer, struct entity entity, float fovFactor);
void loadEntityFromObjFile(char *filePath, struct entity *entity);
void pushVector(struct entity *entity, struct vector3D vector3D);
void pushTriangle(struct entity *entity, struct triangle triangle);
void translateEntity(struct entity *entity, struct vector3D translation);

#endif // !_3DSR_ENTITY
