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

#ifndef _3DSR_MATRICES

#include "vector.h"
#include "common.h"

struct Matrix4x4 {
  float m[4][4];
};

struct Matrix4x4 get4x4Identity(void);
struct Matrix4x4 get4x4Scale(float sx, float sy, float sz);
struct Matrix4x4 get4x4Translation(float tx, float ty, float tz);
struct Matrix4x4 get4x4RotationX(float beta);
struct Matrix4x4 get4x4RotationY(float beta);
struct Matrix4x4 get4x4RotationZ(float beta);
struct Matrix4x4 get4x4Rotation(float betaX, float betaY, float betaZ);
struct vector3D get4x4ByVector3DProduct(struct Matrix4x4 *a, struct vector3D *b);
struct Matrix4x4 get4x4By4x4Product(struct Matrix4x4 *a, struct Matrix4x4 *b);
struct Matrix4x4 getWorldMatrix(struct Matrix4x4 scaling, struct Matrix4x4 translation, struct Matrix4x4 rotationX, struct Matrix4x4 rotationY, struct Matrix4x4 rotationZ);
struct Matrix4x4 getViewMatrix(struct camera *camera);
struct Matrix4x4 getProjectionMatrix(float screenHigh, float screenWidth, float verticalFov);
void printMatrix4x4(struct Matrix4x4 m);

#endif // !_3DSR_MATRICES
