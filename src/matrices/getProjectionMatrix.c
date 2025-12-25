// This file is part of 3dsr.
// Copyright (C) 2025 Kenedy Henrique Bueno Silva

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

#include "matrices.h"
#include <math.h>
#include <stdint.h>

struct Matrix4x4 getProjectionMatrix(float screenHigh, float screenWidth, float verticalFov) {
  float zfar = 200.0f, znear = 1.0f;
  struct Matrix4x4 projectionMatrix = get4x4Identity();
  projectionMatrix.m[3][3] = 0.0f;

  float aspectRatio = screenHigh/screenWidth;
  float fov = 1/tan(verticalFov/2);
  // x scaling
  projectionMatrix.m[0][0] = fov*aspectRatio;

  // y scaling
  projectionMatrix.m[1][1] = fov;

  // z scaling
  // float lambda = zfar / (zfar - znear);
  projectionMatrix.m[2][2] = zfar/(zfar-znear);
  projectionMatrix.m[2][3] = ((zfar/(zfar-znear))*znear);

  projectionMatrix.m[3][2] = 1.0f;

  return projectionMatrix;
}
