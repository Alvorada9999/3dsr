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

void merge(struct triangle *triangles, uint32_t left, uint32_t mid, uint32_t right) {
  uint32_t i, j, k;
  uint32_t n1 = mid - left + 1;
  uint32_t n2 = right - mid;

  // Create temporary arrays
  struct triangle leftArr[n1], rightArr[n2];

  // Copy data to temporary arrays
  for (i = 0; i < n1; i++)
    leftArr[i] = triangles[left + i];
  for (j = 0; j < n2; j++)
    rightArr[j] = triangles[mid + 1 + j];

  // Merge the temporary arrays back into arr[left..right]
  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (leftArr[i].deep <= rightArr[j].deep) {
      triangles[k] = leftArr[i];
      i++;
    }
    else {
      triangles[k] = rightArr[j];
      j++;
    }
    k++;
  }

  // Copy the remaining elements of leftArr[], if any
  while (i < n1) {
    triangles[k] = leftArr[i];
    i++;
    k++;
  }

  // Copy the remaining elements of rightArr[], if any
  while (j < n2) {
    triangles[k] = rightArr[j];
    j++;
    k++;
  }
}

// The subarray to be sorted is in the index range [left-right]
void mergeSort(struct triangle *triangles, uint32_t left, uint32_t right) {
  if (left < right) {

    // Calculate the midpoint
    uint32_t mid = left + (right - left) / 2;

    // Sort first and second halves
    mergeSort(triangles, left, mid);
    mergeSort(triangles, mid + 1, right);

    // Merge the sorted halves
    merge(triangles, left, mid, right);
  }
}

void sortTrianglesByDeep(struct triangle *triangles, uint32_t trianglesLength, struct vector3D *vectors) {
  for (uint32_t i=0; i<trianglesLength; i++) {
    triangles[i].deep = ((vectors[triangles[i].a].z) + (vectors[triangles[i].b].z) + (vectors[triangles[i].c].z))/3;
  }
  mergeSort(triangles, 0, trianglesLength);
}

uint8_t renderOption = RENDER_OPTION_WIREFRAME_AND_FACES;

extern struct collorBuffer *collorBuffer;

void performPerspectiveProjectionOnEntity(struct entity entity, float fovFactor) {
  static struct vector3D vertexA, vertexB, vertexC;

  //Painter's algorithm usage, at some point in the future the z buffer solution will be used instead
  sortTrianglesByDeep(entity.triangles, entity.trianglesLength-1, entity.transformedVectors);

  for(uint32_t i=0; i<entity.trianglesLength; i++) {
    vertexA = entity.transformedVectors[entity.triangles[i].a-1];
    vertexB = entity.transformedVectors[entity.triangles[i].b-1];
    vertexC = entity.transformedVectors[entity.triangles[i].c-1];

    if(shouldCull(vertexA, vertexB, vertexC, (struct vector3D){ .x = 0, .y = 0, .z = 0 })) continue;
    vertexA.x = round((vertexA.x)/(vertexA.z) * fovFactor);
    vertexA.y = round((vertexA.y)/(vertexA.z) * fovFactor);

    vertexB.x = round((vertexB.x)/(vertexB.z) * fovFactor);
    vertexB.y = round((vertexB.y)/(vertexB.z) * fovFactor);

    vertexC.x = round((vertexC.x)/(vertexC.z) * fovFactor);
    vertexC.y = round((vertexC.y)/(vertexC.z) * fovFactor);

    // some addition is being added to the draw position to move the projection to the center of the screen /////////////////

    if(renderOption == RENDER_OPTION_ONLY_VECTORS) {
      drawPixel(collorBuffer, vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, 0xFFFF75CE);
      drawPixel(collorBuffer, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, 0xFFFF75CE);
      drawPixel(collorBuffer, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, 0xFFFF75CE);
      continue;
    }

    if(renderOption == RENDER_OPTION_ONLY_FACES || renderOption == RENDER_OPTION_WIREFRAME_AND_FACES) {
      fillTriangle(vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, 0xFFFCFF75);
    }

    if(renderOption == RENDER_OPTION_ONLY_WIREFRAME || renderOption == RENDER_OPTION_WIREFRAME_AND_FACES) {
      drawLineDDA(collorBuffer, vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, 0xFFFF75CE);
      drawLineDDA(collorBuffer, vertexB.x+collorBuffer->width/2.0, vertexB.y+collorBuffer->height/2.0, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, 0xFFFF75CE);
      drawLineDDA(collorBuffer, vertexC.x+collorBuffer->width/2.0, vertexC.y+collorBuffer->height/2.0, vertexA.x+collorBuffer->width/2.0, vertexA.y+collorBuffer->height/2.0, 0xFFFF75CE);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }
}
