// This file is part of 3dsr.
// Copyright (C) 2024 Kenedy Henrique Bueno Silva

// donttrust is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <SDL2/SDL_timer.h>
#include <errno.h>

#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "entity.h"
#include "input.h"
#include "error.h"
#include "vector.h"

int32_t main(void) {
  struct SDL *sdl = initSdl();
  struct collorBuffer *collorBuffer = createCollorBuffer(sdl->renderer, sdl->windowWidth, sdl->windowHeight);

  bool isRunning = true;

  //===============================================================================
  struct entity cube;
  cube.arrayOfVectors = malloc(sizeof(struct vector3D)*8);
  if(cube.arrayOfVectors == NULL && errno == ENOMEM) errExit(1);
  cube.numberOfVectors = 8;
  cube.triangles = malloc(sizeof(struct triangle)*12);
  if(cube.triangles == NULL && errno == ENOMEM) errExit(1);
  cube.numberOfTriangles = 12;
  cube.arrayOfVectors[0] = (struct vector3D){ .x = -1, .y = -1, .z = -1 }; // 1
  cube.arrayOfVectors[1] = (struct vector3D){ .x = -1, .y =  1, .z = -1 }; // 2
  cube.arrayOfVectors[2] = (struct vector3D){ .x =  1, .y =  1, .z = -1 }; // 3
  cube.arrayOfVectors[3] = (struct vector3D){ .x =  1, .y = -1, .z = -1 }; // 4
  cube.arrayOfVectors[4] = (struct vector3D){ .x =  1, .y =  1, .z =  1 }; // 5
  cube.arrayOfVectors[5] = (struct vector3D){ .x =  1, .y = -1, .z =  1 }; // 6
  cube.arrayOfVectors[6] = (struct vector3D){ .x = -1, .y =  1, .z =  1 }; // 7
  cube.arrayOfVectors[7] = (struct vector3D){ .x = -1, .y = -1, .z =  1 }; // 8
  // front
  cube.triangles[0] = (struct triangle){ .a = 1, .b = 2, .c = 3 };
  cube.triangles[1] = (struct triangle){ .a = 1, .b = 3, .c = 4 };
  // right
  cube.triangles[2] = (struct triangle){ .a = 4, .b = 3, .c = 5 };
  cube.triangles[3] = (struct triangle){ .a = 4, .b = 5, .c = 6 };
  // back
  cube.triangles[4] = (struct triangle){ .a = 6, .b = 5, .c = 7 };
  cube.triangles[5] = (struct triangle){ .a = 6, .b = 7, .c = 8 };
  // left
  cube.triangles[6] = (struct triangle){ .a = 8, .b = 7, .c = 2 };
  cube.triangles[7] = (struct triangle){ .a = 8, .b = 2, .c = 1 };
  // top
  cube.triangles[8] = (struct triangle){ .a = 2, .b = 7, .c = 5 };
  cube.triangles[9] = (struct triangle){ .a = 2, .b = 5, .c = 3 };
  // bottom
  cube.triangles[10] = (struct triangle){ .a = 6, .b = 8, .c = 1 };
  cube.triangles[11] = (struct triangle){ .a = 6, .b = 1, .c = 4 };
  //===============================================================================

  struct vector3D rotationVector = { .x = 1.0, .y = 1.5807, .z = 2.0 };
  uint64_t lastFrameTime = 0;
  float deltaTime = 0;
  while(isRunning) {
    getInput();
    deltaTime = SDL_GetTicks64() - lastFrameTime;
    for(uint32_t i=0; i<cube.numberOfVectors; i++) {
      rotateXVector3D(&cube.arrayOfVectors[i], rotationVector.x*deltaTime/1000);
      rotateYVector3D(&cube.arrayOfVectors[i], rotationVector.y*deltaTime/1000);
      rotateZVector3D(&cube.arrayOfVectors[i], rotationVector.z*deltaTime/1000);
    }
    render(sdl, collorBuffer, &cube, 1);
    lastFrameTime = SDL_GetTicks64();
    SDL_Delay(1000/60);
  }
}
