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

#include "common.h"
#include "vector.h"

bool shouldCull(struct entity entity, struct vector3D vertexA, struct vector3D vertexB, struct vector3D vertexC, struct vector3D camera) {
  vertexA.x += entity.currentXTranslation;
  vertexA.y += entity.currentYTranslation;
  vertexA.z += entity.currentZTranslation;
  vertexB.x += entity.currentXTranslation;
  vertexB.y += entity.currentYTranslation;
  vertexB.z += entity.currentZTranslation;
  vertexC.x += entity.currentXTranslation;
  vertexC.y += entity.currentYTranslation;
  vertexC.z += entity.currentZTranslation;
  struct vector3D v1, v2, faceNormal, cameraRay;

  v1 = subtract3DVectors(vertexB, vertexA);
  v2 = subtract3DVectors(vertexC, vertexA);
  faceNormal = getCrossProduct(v1, v2);

  //don't matter wich vertex, I just want a vector coming from the camera to the face
  cameraRay = subtract3DVectors(camera, vertexA);

  if(getDotProduct(faceNormal, cameraRay) <= 0) {
    return true;
  } else return false;
}
