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
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "entity.h"
#include "error.h"
#include "vector.h"

#define LOOKING_FOR_FACES_AND_VERTICES 0
#define PARSING_VERTEX 1
#define PARSING_FACE 2

void loadEntityFromObjFile(char *filePath, struct entity *entity) {
  uint8_t currentTask = LOOKING_FOR_FACES_AND_VERTICES;
  int8_t fd = open(filePath, O_RDONLY);
  if(fd == -1) errExit(9);

  int16_t readSize = -1;
  uint8_t buffer[BUFSIZ], lastChar;
  while(readSize != 0) {
    readSize = read(fd, buffer, 1024);
    if(readSize == -1) continue;
    if(readSize == 0) break;
    for(int16_t i=0; i<readSize; i++) {
      switch (currentTask) {
        case LOOKING_FOR_FACES_AND_VERTICES:
          if(lastChar == 'v' && buffer[i] == ' ') { currentTask = PARSING_VERTEX; break; }
          if(lastChar == 'f' && buffer[i] == ' ') { currentTask = PARSING_FACE; break; }
          break;
        case PARSING_VERTEX: {
          static uint8_t currentVertexToGet = 'x';
          static uint8_t currentAxisValue[10]  = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
          static uint8_t currentAxisLenght = 0;
          static struct vector3D vertex;
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
                vertex.z = vertex.z;
                currentVertexToGet = 'x';
                currentAxisLenght = 0;
                memset(currentAxisValue, 0, 10);
                currentTask = LOOKING_FOR_FACES_AND_VERTICES;
                pushVector(entity, vertex);
                break;
              }
              currentAxisValue[currentAxisLenght] = buffer[i];
              currentAxisLenght++;
              break;
          }
          break;
        }
        case PARSING_FACE: {
          static struct triangle triangle = { 0, 0, 0, 0 };
          static uint8_t currentVertexIndexToGet = 'a';
          static uint8_t faceBuffer[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, faceBufferLength = 0;
          static bool ignoreUntilSpace = false;
          if(ignoreUntilSpace) {
            if(buffer[i] == ' ') ignoreUntilSpace = false;
            break;
          }

          switch (currentVertexIndexToGet) {
            case 'a':
              if(buffer[i] < 48 || buffer[i] > 57) {
                triangle.a = strtoul((char *)faceBuffer, NULL, 10);
                currentVertexIndexToGet = 'b';
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
                currentVertexIndexToGet = 'c';
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
                currentVertexIndexToGet = 'a';
                faceBufferLength = 0;
                memset(faceBuffer, 0, 10);
                currentTask = LOOKING_FOR_FACES_AND_VERTICES;
                pushTriangle(entity,  triangle);
                break;
              }
              faceBuffer[faceBufferLength] = buffer[i];
              faceBufferLength ++;
              break;
          }

          break;
        }
      }
      lastChar = buffer[i];
    }
  }
}
