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

void performPerspectiveProjectionOnEntity(struct collorBuffer *collorBuffer, struct entity entity, float fovFactor, struct vector3D translation) {
  static struct vector2D projectedVertexA, projectedVertexB, projectedVertexC;
  for(uint32_t i=0; i<entity.trianglesLength; i++) {
    projectedVertexA.x = (entity.vectors[entity.triangles[i].a-1].x+translation.x)*fovFactor/(entity.vectors[entity.triangles[i].a-1].z+translation.z);
    projectedVertexA.y = (entity.vectors[entity.triangles[i].a-1].y+translation.y)*fovFactor/(entity.vectors[entity.triangles[i].a-1].z+translation.z);

    projectedVertexB.x = (entity.vectors[entity.triangles[i].b-1].x+translation.x)*fovFactor/(entity.vectors[entity.triangles[i].b-1].z+translation.z);
    projectedVertexB.y = (entity.vectors[entity.triangles[i].b-1].y+translation.y)*fovFactor/(entity.vectors[entity.triangles[i].b-1].z+translation.z);

    projectedVertexC.x = (entity.vectors[entity.triangles[i].c-1].x+translation.x)*fovFactor/(entity.vectors[entity.triangles[i].c-1].z+translation.z);
    projectedVertexC.y = (entity.vectors[entity.triangles[i].c-1].y+translation.y)*fovFactor/(entity.vectors[entity.triangles[i].c-1].z+translation.z);

    // some addition is being added to the draw position to move the projection to the center of the screen
    drawPixel(collorBuffer, projectedVertexA.x+collorBuffer->width/2.0, projectedVertexA.y+collorBuffer->height/2.0, 0xFFFC0FC0);
    drawPixel(collorBuffer, projectedVertexB.x+collorBuffer->width/2.0, projectedVertexB.y+collorBuffer->height/2.0, 0xFFFC0FC0);
    drawPixel(collorBuffer, projectedVertexC.x+collorBuffer->width/2.0, projectedVertexC.y+collorBuffer->height/2.0, 0xFFFC0FC0);
    drawLineDDA(collorBuffer, projectedVertexA.x+1440.0/2, projectedVertexA.y+900.0/2, projectedVertexB.x+1440.0/2, projectedVertexB.y+900.0/2, 0xFFFC0FC0);
    drawLineDDA(collorBuffer, projectedVertexB.x+1440.0/2, projectedVertexB.y+900.0/2, projectedVertexC.x+1440.0/2, projectedVertexC.y+900.0/2, 0xFFFC0FC0);
    drawLineDDA(collorBuffer, projectedVertexC.x+1440.0/2, projectedVertexC.y+900.0/2, projectedVertexA.x+1440.0/2, projectedVertexA.y+900.0/2, 0xFFFC0FC0);
  }
}
