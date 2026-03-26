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

#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "entity.h"
#include "error.h"
#include "vector.h"

#define LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES 0
#define PARSING_VERTEX 1
#define PARSING_FACE 2
#define PARSING_TEXTURE_COORDINATES 3
#define A_UV 4
#define B_UV 5 
#define C_UV 6 

extern struct vector3D initialPosition;

//I know there are many improvements for this function, it's not being very efficient as is
void loadEntityFromObjFile(char *filePath, struct entity *entity) {
  //
  struct textureUvHolder *texture_uv_holder = malloc(sizeof(struct textureUvHolder));
  uint32_t texture_uv_holder_lenght = 1;
  struct vectorTextureUvCoordinates *uvArray = NULL;
  uint32_t uvArrayLenght = 0;

  //those are used to store information used to decide
  //the initial position for the entity model
  float verticalLength = 0, horizontalLength = 0;
  float biggestPositveX = 0, biggestPositveY = 0, biggestPositveZ = 0;
  float smallestNegativeX = 0, smallestNegativeY = 0;

  uint8_t currentTask = LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES;
  int8_t fd = open(filePath, O_RDONLY);
  if(fd == -1) errExit(9);

  int16_t readSize = -1;
  uint8_t buffer[BUFSIZ], lastChar = '\n';
  while(readSize != 0) {
    readSize = read(fd, buffer, BUFSIZ);
    if(readSize == -1) continue;
    if(readSize == 0) break;
    for(int16_t i=0; i<readSize; i++) {
      switch (currentTask) {
        case LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES:
          if(lastChar == 'v' && buffer[i] == ' ') { currentTask = PARSING_VERTEX; break; }
          if(lastChar == 'f' && buffer[i] == ' ') { currentTask = PARSING_FACE; break; }
          if(lastChar == 'v' && buffer[i] == 't') { currentTask = PARSING_TEXTURE_COORDINATES; break; }
          break;
        case PARSING_VERTEX: {
          static uint8_t currentVertexToGet = 'x';
          static uint8_t currentAxisValue[10]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
          static uint8_t currentAxisLenght = 0;
          static struct vector3D vertex = {0};
          vertex.w = 1.0f;
          switch (currentVertexToGet) {
            case 'x':
              if((buffer[i] < 48 || buffer[i] > 57) && (buffer[i] != '-' && buffer[i] != '.')) {
                vertex.x = strtof((char *)currentAxisValue, NULL);
                currentVertexToGet = 'y';
                currentAxisLenght = 0;
                memset(currentAxisValue, 0, 10);
                break;
              }
              currentAxisValue[currentAxisLenght] = buffer[i];
              currentAxisLenght++;
              break;
            case 'y':
              if((buffer[i] < 48 || buffer[i] > 57) && (buffer[i] != '-' && buffer[i] != '.')) {
                vertex.y = strtof((char *)currentAxisValue, NULL);
                currentVertexToGet = 'z';
                currentAxisLenght = 0;
                memset(currentAxisValue, 0, 10);
                break;
              }
              currentAxisValue[currentAxisLenght] = buffer[i];
              currentAxisLenght++;
              break;
            case 'z':
              if((buffer[i] < 48 || buffer[i] > 57) && (buffer[i] != '-' && buffer[i] != '.')) {
                vertex.z = strtof((char *)currentAxisValue, NULL);
                currentVertexToGet = 'x';
                currentAxisLenght = 0;
                memset(currentAxisValue, 0, 10);
                currentTask = LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES;
                pushVector(entity, vertex);

                if(vertex.x > biggestPositveX) biggestPositveX = vertex.x;
                if(vertex.x < smallestNegativeX) smallestNegativeX = vertex.x;
                if(vertex.y > biggestPositveY) biggestPositveY = vertex.y;
                if(vertex.y < smallestNegativeY) smallestNegativeY = vertex.y;
                if(vertex.z > biggestPositveZ) biggestPositveZ = vertex.z;

                break;
              }
              currentAxisValue[currentAxisLenght] = buffer[i];
              currentAxisLenght++;
              break;
          }
          break;
        }
        case PARSING_FACE: {
          static struct triangle triangle = { {0, 0}, {0, 0}, {0, 0}, 0, 0, 0, 0 };
          static uint8_t currentIndexToGet = 'a';
          static uint8_t faceBuffer[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, faceBufferLength = 0;
          static bool ignoreUntilSpace = false;
          if(ignoreUntilSpace) {
            if(buffer[i] == ' ') ignoreUntilSpace = false;
            break;
          }

          switch (currentIndexToGet) {
            case 'a':
              if(buffer[i] < 48 || buffer[i] > 57) {
                triangle.a = strtoul((char *)faceBuffer, NULL, 10);
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                if(buffer[i] == '/') currentIndexToGet = A_UV;
                else {
                  currentIndexToGet = 'b';
                  ignoreUntilSpace = true;
                }
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
            case A_UV:
              if(buffer[i] < 48 || buffer[i] > 57) {
                texture_uv_holder[texture_uv_holder_lenght-1].a_uvIndex = strtoul((char *)faceBuffer, NULL, 10);
                currentIndexToGet = 'b';
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                if(buffer[i] != ' ') ignoreUntilSpace = true;
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
            case 'b':
              if(buffer[i] < 48 || buffer[i] > 57) {
                triangle.b = strtoul((char *)faceBuffer, NULL, 10);
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                if(buffer[i] == '/') currentIndexToGet = B_UV;
                else {
                  currentIndexToGet = 'c';
                  ignoreUntilSpace = true;
                }
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
            case B_UV:
              if(buffer[i] < 48 || buffer[i] > 57) {
                texture_uv_holder[texture_uv_holder_lenght-1].b_uvIndex = strtoul((char *)faceBuffer, NULL, 10);
                currentIndexToGet = 'c';
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                if(buffer[i] != ' ') ignoreUntilSpace = true;
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
            case 'c':
              if(buffer[i] < 48 || buffer[i] > 57) {
                triangle.c = strtoul((char *)faceBuffer, NULL, 10);
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                if(buffer[i] == '/') currentIndexToGet = C_UV;
                else {
                  currentIndexToGet = 'a';
                  currentTask = LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES;
                  pushTriangle(entity,  triangle);
                }
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
            case C_UV:
              if(buffer[i] < 48 || buffer[i] > 57) {
                texture_uv_holder[texture_uv_holder_lenght-1].c_uvIndex = strtoul((char *)faceBuffer, NULL, 10);
                texture_uv_holder[texture_uv_holder_lenght-1].triangleIndex = entity->trianglesLength+1;
                currentIndexToGet = 'a';
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                currentTask = LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES;
                pushTriangle(entity,  triangle);
                texture_uv_holder = realloc(texture_uv_holder, sizeof(struct textureUvHolder)+texture_uv_holder_lenght*sizeof(struct textureUvHolder));
                texture_uv_holder_lenght++;
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
          }

          break;
        }
        case PARSING_TEXTURE_COORDINATES: {
          static uint8_t currentTextureCoordinateToGet = 'u';
          static uint8_t textureUvBuffer[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
          static uint8_t currentTextureUvLenght = 0;
          static struct vectorTextureUvCoordinates vT = { 0, 0};
          static bool startedNow = true;
          //in order to skip the first ' ' (space)
          if(startedNow) {
            startedNow = false;
            break;
          }

          switch (currentTextureCoordinateToGet) {
            case 'u':
              if((buffer[i] < 48 || buffer[i] > 57) && buffer[i] != '.') {
                vT.u = strtof((char *)textureUvBuffer, NULL);
                currentTextureCoordinateToGet = 'v';
                currentTextureUvLenght = 0;
                memset(textureUvBuffer, 0, 10);
                break;
              }
              textureUvBuffer[currentTextureUvLenght] = buffer[i];
              currentTextureUvLenght++;
              break;
            case 'v':
              if((buffer[i] < 48 || buffer[i] > 57) && buffer[i] != '.') {
                vT.v = strtof((char *)textureUvBuffer, NULL);
                currentTextureCoordinateToGet = 'u';
                currentTextureUvLenght = 0;
                memset(textureUvBuffer, 0, 10);
                currentTask = LOOKING_FOR_FACES_AND_VERTICES_AND_TEXTURE_COORDINATES;
                startedNow = true;
                uvArray = addNewUV(&uvArrayLenght, uvArray, vT);
                break;
              }
              textureUvBuffer[currentTextureUvLenght] = buffer[i];
              currentTextureUvLenght++;
              break;
          }
          break;
        }
      }
      lastChar = buffer[i];
    }
  }

  //it ends at texture_uv_holder_lenght-1 because 
  //there's always an empty position at the end
  for (uint32_t i=0; i<texture_uv_holder_lenght-1; i++) {
    entity->triangles[texture_uv_holder[i].triangleIndex].b_uv = uvArray[texture_uv_holder[i].b_uvIndex];
    entity->triangles[texture_uv_holder[i].triangleIndex].c_uv = uvArray[texture_uv_holder[i].c_uvIndex];
  }

  free(uvArray);
  free(texture_uv_holder);

  horizontalLength = fabs(smallestNegativeX) + biggestPositveX;
  verticalLength = fabs(smallestNegativeY) + biggestPositveY;
  if(fabs(smallestNegativeY) != biggestPositveY) {
    if(fabs(smallestNegativeY) > biggestPositveY) {
      initialPosition.y = (verticalLength/2) - biggestPositveY;
    } else {
      initialPosition.y = 0 - ((verticalLength/2) - fabs(smallestNegativeY));
    }
  }
  if(fabs(smallestNegativeX) != biggestPositveX) {
    if(fabs(smallestNegativeX) > biggestPositveX) {
      initialPosition.x = (horizontalLength/2) - biggestPositveX;
    } else {
      initialPosition.x = 0 - ((horizontalLength/2) - fabs(smallestNegativeX));
    }
  }
  float bigger = 0;
  if(horizontalLength > bigger) bigger = horizontalLength;
  if(verticalLength > bigger) bigger = verticalLength;
  if(biggestPositveZ > bigger) bigger = biggestPositveZ;
  initialPosition.z = 0 + bigger;

  entity->transformedVectors = malloc(sizeof(struct vector3D)*entity->vectorsLength);
  memset(entity->transformedVectors, 0, sizeof(struct vector3D)*entity->vectorsLength);

}
