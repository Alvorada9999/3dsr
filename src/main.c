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
#include "vector.h"
#include "init.h"

//those values are just for testing purposes
#define CAMERA_POSITION_X_AXIS 0
#define CAMERA_POSITION_Z_AXIS -140
#define CAMERA_POSITION_Y_AXIS -40

int32_t main(int32_t argc, char *argv[]) {
  struct SDL *sdl = initSdl();
  struct collorBuffer *collorBuffer = createCollorBuffer(sdl->renderer, sdl->windowWidth, sdl->windowHeight);

  bool isRunning = true;
  
  struct entity entity;
  entity.currentXTranslation = 0;
  entity.currentYTranslation = 0;
  entity.currentZTranslation = 0;
  struct programOptions programOptions = getProgramOptions(argc, argv);
  loadEntityFromObjFile(programOptions.objFilePath, &entity);

  translateEntity(&entity, (struct vector3D){ .x = CAMERA_POSITION_X_AXIS, .y = CAMERA_POSITION_Y_AXIS, .z = CAMERA_POSITION_Z_AXIS });

  struct vector3D rotationVector = { .x = 0.0, .y = 1.5, .z = 0.0 };
  uint64_t lastFrameTime = 0;
  float deltaTime = 0;
  while(isRunning) {
    getInput();
    deltaTime = SDL_GetTicks64() - lastFrameTime;
    for(uint32_t i=0; i<entity.vectorsLength; i++) {
      rotateXVector3D(&entity.vectors[i], rotationVector.x*deltaTime/1000);
      rotateYVector3D(&entity.vectors[i], rotationVector.y*deltaTime/1000);
      rotateZVector3D(&entity.vectors[i], rotationVector.z*deltaTime/1000);
    }
    render(sdl, collorBuffer, &entity, 1);
    lastFrameTime = SDL_GetTicks64();
    SDL_Delay(1000/60);
  }
}
