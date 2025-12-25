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

#include <SDL2/SDL_timer.h>

#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "entity.h"
#include "input.h"
#include "init.h"
#include "matrices.h"
#include "vector.h"

struct collorBuffer *collorBuffer;
struct vector3D cameraEye = {0, 0, 0, 1};
struct Matrix4x4 translationMatrix;

struct vector3D initialPosition = { .x = 0, .y = 0, .z = 0 };
struct SDL *sdl;

int32_t main(int32_t argc, char *argv[]) {
  sdl = initSdl();
  collorBuffer = createCollorBuffer(sdl->renderer, sdl->windowWidth, sdl->windowHeight);

  bool isRunning = true;
  
  struct entity entity = getNewEntity();
  struct programOptions programOptions = getProgramOptions(argc, argv);
  loadEntityFromObjFile(programOptions.objFilePath, &entity);

  struct Matrix4x4 rotationMatrix = get4x4Identity();
  translationMatrix = get4x4Translation(initialPosition.x, initialPosition.y, initialPosition.z);
  struct Matrix4x4 worldMatrix = get4x4Identity();

  uint64_t lastFrameTime = 0;
  float deltaTimeInSeconds = 0;
  struct camera camera = {
    .eye = {0, 0, 0, 1},
    .target = {camera.eye.x, camera.eye.y, camera.eye.z - 200.0, 1},
    .up = {0, 1, 0, 1}
  };
  while(isRunning) {
    // Wait some time until reaching the target frame time in milliseconds
    int32_t timeToWait = TARGET_FRAME_TIME - (SDL_GetTicks64() - lastFrameTime);
    // Only delay execution if we are running too fast
    if (timeToWait > 0 && timeToWait <= TARGET_FRAME_TIME) {
      SDL_Delay((uint64_t)timeToWait);
    }
    deltaTimeInSeconds = (SDL_GetTicks64() - lastFrameTime)/1000.0f;
    lastFrameTime = SDL_GetTicks64();

    getInput();

    static struct vector3D rotationVectorSpeedInSeconds = { .x = 0.0, .y = 1.5, .z = 0.0 };
    struct Matrix4x4 r = get4x4Rotation(rotationVectorSpeedInSeconds.x*deltaTimeInSeconds, rotationVectorSpeedInSeconds.y*deltaTimeInSeconds, rotationVectorSpeedInSeconds.z*deltaTimeInSeconds);
    rotationMatrix = get4x4By4x4Product(&r, &rotationMatrix);

    worldMatrix = get4x4Identity();
    worldMatrix = get4x4By4x4Product(&translationMatrix, &rotationMatrix);

    //cameraEye is updated by user input
    camera.eye = cameraEye;

    struct Matrix4x4 viewMatrix = getViewMatrix(&camera);
    worldMatrix = get4x4By4x4Product(&viewMatrix, &worldMatrix);

    for(uint32_t i=0; i<entity.vectorsLength; i++) {
      entity.transformedVectors[i] = get4x4ByVector3DProduct(&worldMatrix, &entity.vectors[i]);
    }
    render(sdl, collorBuffer, &entity, 1);
  }
}
