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

#include <stdlib.h>
#include <errno.h>

#include "entity.h"
#include "error.h"

void pushTriangle(struct entity *entity, struct triangle triangle) {
  if(entity->triangles == NULL) {
    entity->triangles = malloc(sizeof(struct triangle));
    if(entity->triangles == NULL && errno == ENOMEM) errExit(1);
    entity->trianglesLength = 1;
    entity->trianglesSize = 1;
    entity->triangles[0] = triangle;
  } else {
    entity->triangles = realloc(entity->triangles, sizeof(struct triangle)+entity->trianglesLength*sizeof(struct triangle));
    if(entity->triangles == NULL && errno == ENOMEM) errExit(1);
    entity->trianglesLength++;
    entity->trianglesSize++;
    entity->triangles[entity->trianglesLength-1] = triangle;
  }
}
