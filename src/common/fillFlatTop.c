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

extern struct collorBuffer *collorBuffer;

void fillFlatTop(int32_t bottomX, int32_t bottomY, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t argb8888) {
  //if the triangle bottomY is negative, it means all of it is outside screen
  if(bottomY < 0) return;
  //if the flat top is past the screen height, it means all of it is outside screen
  if(y2 > collorBuffer->height) return;

  float inverseSlope1, inverseSlope2;
  inverseSlope1 = (bottomX-x1);
  if(bottomY-y1!=0) inverseSlope1 /= bottomY-y1;
  inverseSlope2 = (bottomX-x2);
  if(bottomY-y2!=0) inverseSlope2 /= bottomY-y2;

  float from = bottomX, to = bottomX;
  //if bottomY is bigger than screen high, it means the triangle begins outside the
  //screen, that being the case, the loop is started from y=screen high to only
  //render what is on the screen
  int32_t startFrom = bottomY;
  if(bottomY > collorBuffer->height) {
    startFrom = collorBuffer->height;
    from -= (bottomY-collorBuffer->height)*inverseSlope1;
    to -= (bottomY-collorBuffer->height)*inverseSlope2;
  }
  //don't render past screen even if the triangle still goes on past it
  int32_t until = y2 < 0 ? 0 : y2;
  for(int32_t y=startFrom; y>=until; y--) {
    drawLineDDA(collorBuffer, from, y, to, y, argb8888);
    from -= inverseSlope1;
    to -= inverseSlope2;
  }
}
