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
#include <stdint.h>

//each value is used to acess an index from an array of vector3D
struct triangle {
  uint32_t a;
  float a_uv;
  uint32_t b;
  float b_uv;
  uint32_t c;
  float c_uv;
  float deep;
};

struct vectorTextures {
  float u;
  float v;
};

struct entity {
  struct triangle *triangles;
  struct vector3D *vectors;
  struct vector3D *transformedVectors;
  struct vectorTextures *vectorTextures;
  uint32_t vectorsLength;
  uint32_t trianglesLength;
  uint32_t vectorsTextureLength;
};

struct entity getNewEntity(void);
void performPerspectiveProjectionOnEntity(struct entity entity);
void loadEntityFromObjFile(char *filePath, struct entity *entity);
void pushVector(struct entity *entity, struct vector3D vector3D);
void pushTriangle(struct entity *entity, struct triangle triangle);
void translateEntity(struct entity *entity, struct vector3D translation);
void pushVectorTexture(struct entity *entity, struct vectorTextures vectorTextures);

#endif // !_3DSR_ENTITY
