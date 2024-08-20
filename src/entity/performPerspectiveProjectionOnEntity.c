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

#include <math.h>

#include "common.h"
#include "entity.h"
#include "vector.h"

extern struct collorBuffer *collorBuffer;

void performPerspectiveProjectionOnEntity(struct entity entity, float fovFactor) {
  static struct vector3D vertexA, vertexB, vertexC;
  for(uint32_t i=0; i<entity.trianglesLength; i++) {
    vertexA = entity.vectors[entity.triangles[i].a-1];
    vertexB = entity.vectors[entity.triangles[i].b-1];
    vertexC = entity.vectors[entity.triangles[i].c-1];

    if(shouldCull(entity, vertexA, vertexB, vertexC, (struct vector3D){ .x = 0, .y = 0, .z = 0 })) continue;
    vertexA.x = round((vertexA.x+entity.currentXTranslation)/(vertexA.z+entity.currentZTranslation) * fovFactor);
    vertexA.y = round((vertexA.y+entity.currentYTranslation)/(vertexA.z+entity.currentZTranslation) * fovFactor);

    vertexB.x = round((vertexB.x+entity.currentXTranslation)/(vertexB.z+entity.currentZTranslation) * fovFactor);
    vertexB.y = round((vertexB.y+entity.currentYTranslation)/(vertexB.z+entity.currentZTranslation) * fovFactor);

    vertexC.x = round((vertexC.x+entity.currentXTranslation)/(vertexC.z+entity.currentZTranslation) * fovFactor);
    vertexC.y = round((vertexC.y+entity.currentYTranslation)/(vertexC.z+entity.currentZTranslation) * fovFactor);

    // some addition is being added to the draw position to move the projection to the center of the screen
    fillTriangle(vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, 0xFFFCFF75);
    drawPixel(collorBuffer, vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, 0xFFFF75CE);
    drawPixel(collorBuffer, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, 0xFFFF75CE);
    drawPixel(collorBuffer, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, 0xFFFF75CE);
    drawLineDDA(collorBuffer, vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, 0xFFFF75CE);
    drawLineDDA(collorBuffer, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, 0xFFFF75CE);
    drawLineDDA(collorBuffer, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, 0xFFFF75CE);
  }
}
