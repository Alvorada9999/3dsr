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
#include <stdio.h>

#include "common.h"
#include "entity.h"
#include "input.h"
#include "init.h"
#include "matrices.h"

struct collorBuffer *collorBuffer;

//those values are just for testing purposes
#define CAMERA_POSITION_X_AXIS 0
#define CAMERA_POSITION_Z_AXIS 0 
#define CAMERA_POSITION_Y_AXIS 0
struct vector3D rotationVectorSpeedInSeconds = { .x = 0.0, .y = 1.5, .z = 0.0 };
struct vector3D initialPosition = { .x = 0, .y = 0, .z = 0 };
float fovFactor = 0;

int32_t main(int32_t argc, char *argv[]) {
  struct SDL *sdl = initSdl();
  collorBuffer = createCollorBuffer(sdl->renderer, sdl->windowWidth, sdl->windowHeight);

  bool isRunning = true;
  
  struct entity entity = getNewEntity();
  struct programOptions programOptions = getProgramOptions(argc, argv);
  loadEntityFromObjFile(programOptions.objFilePath, &entity);

  struct Matrix4x4 translationMatrix = get4x4Translation(initialPosition.x, initialPosition.y, initialPosition.z);

  uint64_t lastFrameTime = 0;
  float deltaTimeInSeconds = 0;
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

    static struct Matrix4x4 rotationMatrix;
    rotationMatrix = get4x4Rotation(rotationVectorSpeedInSeconds.x*deltaTimeInSeconds, rotationVectorSpeedInSeconds.y*deltaTimeInSeconds, rotationVectorSpeedInSeconds.z*deltaTimeInSeconds);
    for(uint32_t i=0; i<entity.vectorsLength; i++) {
      entity.vectors[i] = get4x4ByVector3DProduct(&rotationMatrix, &entity.vectors[i]);
      entity.transformedVectors[i] = get4x4ByVector3DProduct(&translationMatrix, &entity.vectors[i]);
    }
    render(sdl, collorBuffer, &entity, 1);
  }
}
