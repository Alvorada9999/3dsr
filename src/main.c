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
  //making a cube with 9 by 9 by 9 vectors of lenght 2
  struct vector3D *cubeOfPoints = malloc(sizeof(struct vector3D)*9*9*9);
  if(cubeOfPoints == NULL && errno == ENOMEM) errExit(1);
  struct vector2D *projections = malloc(sizeof(struct vector2D)*9*9*9);
  if(projections == NULL && errno == ENOMEM) errExit(1);
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
  cubeOfVectors.arrayOfVectorsProjections = projections;
  cubeOfVectors.numberOfVectors = currentCubeOfPointsPosition;
  //===============================================================================

  float fovFactor = 800;
  struct vector3D rotationVector = { 0.05, 0.05, 0.05 };
  struct vector3D cameraPosition = { 0, 0, -5 };
  while(isRunning) {
    for(uint32_t i=0; i<cubeOfVectors.numberOfVectors; i++) {
      rotateXVector3D(&cubeOfVectors.arrayOfVectors[i], rotationVector.x);
      rotateYVector3D(&cubeOfVectors.arrayOfVectors[i], rotationVector.y);
      rotateZVector3D(&cubeOfVectors.arrayOfVectors[i], rotationVector.z);
    }
    performPerspectiveProjectionOnEntity(cubeOfVectors, fovFactor, cameraPosition.z);
    getInput();
    render(sdl, collorBuffer, &cubeOfVectors, 1);
    SDL_Delay(1000/60);
  }
}
