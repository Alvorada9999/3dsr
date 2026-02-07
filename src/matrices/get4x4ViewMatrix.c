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
#include "vector.h"

//look at implementation
struct Matrix4x4 getViewMatrix(struct camera *camera) {
  struct vector3D z = getNormalizedVector(subtract3DVectors(camera->target, camera->eye));
  struct vector3D x = getNormalizedVector(getCrossProduct(camera->up, z));
  struct vector3D y = getCrossProduct(z, x);

  struct Matrix4x4 viewMatrix = {{
    {x.x, x.y, x.z, -getDotProduct(x, camera->eye)},
    {y.x, y.y, y.z, -getDotProduct(y, camera->eye)},
    {z.x, z.y, z.z, -getDotProduct(z, camera->eye)},
    {0, 0, 0, 1}
  }};

  return viewMatrix;
}
