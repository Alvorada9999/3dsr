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

struct vectorTextureUvCoordinates {
  float u;
  float v;
};

//used only at entity loading time
struct textureUvHolder {
  uint32_t triangleIndex;
  uint32_t a_uvIndex;
  uint32_t b_uvIndex;
  uint32_t c_uvIndex;
};
//

struct triangle {

  //each value is used to acess an index from an array of vectorTextures
  struct vectorTextureUvCoordinates a_uv;
  struct vectorTextureUvCoordinates b_uv;
  struct vectorTextureUvCoordinates c_uv;

  //each value is used to acess an index from an array of vector3D
  uint32_t a;
  uint32_t b;
  uint32_t c;

  float deep;
};

struct entity {
  struct triangle *triangles;
  struct vector3D *vectors;
  struct vector3D *transformedVectors;
  uint32_t vectorsLength;
  uint32_t trianglesLength;
};

struct entity getNewEntity(void);
void performPerspectiveProjectionOnEntity(struct entity entity);
void translateEntity(struct entity *entity, struct vector3D translation);

//these are used at entity loading time only
void loadEntityFromObjFile(char *filePath, struct entity *entity);
struct vectorTextureUvCoordinates* addNewUV(uint32_t *length, struct vectorTextureUvCoordinates *array, struct vectorTextureUvCoordinates vectorTexture);
void pushVector(struct entity *entity, struct vector3D vector3D);
void pushTriangle(struct entity *entity, struct triangle triangle);

#endif // !_3DSR_ENTITY
