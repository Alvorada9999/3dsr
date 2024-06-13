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

#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "entity.h"
#include "input.h"

int32_t main(void) {
  struct SDL *sdl = initSdl();
  struct collorBuffer *collorBuffer = createCollorBuffer(sdl->renderer, sdl->windowWidth, sdl->windowHeight);

  bool isRunning = true;

  //making a cube with 9 by 9 by 9 with lenght 2
  vector3D cubeOfPoints[9*9*9];
  uint16_t currentCubeOfPointsPosition = 0;
  for(float x=-1; x<=1; x += 0.25) {
    for(float y=-1; y<=1; y += 0.25) {
      for(float z=-1; z<=1; z += 0.25) {
        cubeOfPoints[currentCubeOfPointsPosition].x = x;
        cubeOfPoints[currentCubeOfPointsPosition].y = y;
        cubeOfPoints[currentCubeOfPointsPosition].z = z;
        currentCubeOfPointsPosition++;
      }
    }
  }

  struct entity cubeOfVectors;
  cubeOfVectors.arrayOfVectors = cubeOfPoints;
  cubeOfVectors.numberOfVectors = currentCubeOfPointsPosition+1;

  float fovFactor = 128;
  scaleEntity(cubeOfVectors, fovFactor, fovFactor, fovFactor);
  translateEntity(cubeOfVectors, sdl->windowWidth/2, sdl->windowHeight/2, 0);
  while(isRunning) {
    getInput();
    drawEntity(collorBuffer, cubeOfVectors);
    render(sdl, collorBuffer);
    SDL_Delay(1000/60);
  }
}
