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

#include "common.h"
#include "entity.h"
#include "vector.h"

void performPerspectiveProjectionOnEntity(struct collorBuffer *collorBuffer, struct entity entity, float fovFactor) {
  static struct vector2D projectedVertexA, projectedVertexB, projectedVertexC;
  static struct vector3D vertexA, vertexB, vertexC;
  for(uint32_t i=0; i<entity.trianglesLength; i++) {
    vertexA = entity.vectors[entity.triangles[i].a-1];
    vertexB = entity.vectors[entity.triangles[i].b-1];
    vertexC = entity.vectors[entity.triangles[i].c-1];

    if(shouldCull(entity, vertexA, vertexB, vertexC, (struct vector3D){ .x = 0, .y = 0, .z = 0 })) continue;
    projectedVertexA.x = (vertexA.x+entity.currentXTranslation)/(vertexA.z+entity.currentZTranslation);
    projectedVertexA.y = (vertexA.y+entity.currentYTranslation)/(vertexA.z+entity.currentZTranslation);
    projectedVertexA.x *= fovFactor;
    projectedVertexA.y *= fovFactor;

    projectedVertexB.x = (vertexB.x+entity.currentXTranslation)/(vertexB.z+entity.currentZTranslation);
    projectedVertexB.y = (vertexB.y+entity.currentYTranslation)/(vertexB.z+entity.currentZTranslation);
    projectedVertexB.x *= fovFactor;
    projectedVertexB.y *= fovFactor;

    projectedVertexC.x = (vertexC.x+entity.currentXTranslation)/(vertexC.z+entity.currentZTranslation);
    projectedVertexC.y = (vertexC.y+entity.currentYTranslation)/(vertexC.z+entity.currentZTranslation);
    projectedVertexC.x *= fovFactor;
    projectedVertexC.y *= fovFactor;

    // some addition is being added to the draw position to move the projection to the center of the screen
    drawPixel(collorBuffer, projectedVertexA.x+collorBuffer->width/2.0, projectedVertexA.y+collorBuffer->height/2.0, 0xFFFC0FC0);
    drawPixel(collorBuffer, projectedVertexB.x+collorBuffer->width/2.0, projectedVertexB.y+collorBuffer->height/2.0, 0xFFFC0FC0);
    drawPixel(collorBuffer, projectedVertexC.x+collorBuffer->width/2.0, projectedVertexC.y+collorBuffer->height/2.0, 0xFFFC0FC0);
    drawLineDDA(collorBuffer, projectedVertexA.x+1440.0/2, projectedVertexA.y+900.0/2, projectedVertexB.x+1440.0/2, projectedVertexB.y+900.0/2, 0xFFFC0FC0);
    drawLineDDA(collorBuffer, projectedVertexB.x+1440.0/2, projectedVertexB.y+900.0/2, projectedVertexC.x+1440.0/2, projectedVertexC.y+900.0/2, 0xFFFC0FC0);
    drawLineDDA(collorBuffer, projectedVertexC.x+1440.0/2, projectedVertexC.y+900.0/2, projectedVertexA.x+1440.0/2, projectedVertexA.y+900.0/2, 0xFFFC0FC0);
  }
}
