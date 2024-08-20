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

void fillFlatBottom(int32_t topX, int32_t topY, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t argb8888) {
  //if the triangle flat bottom is negative, it means all of it is outside screen
  if(y2 < 0) return;
  //if topY is bigger than screen high, it means all of it is outise the screeen
  if(topY>collorBuffer->height) return;

  float inverseSlope1, inverseSlope2;
  inverseSlope1 = (x1-topX);
  if(y1-topY!=0) inverseSlope1 /= y1-topY;
  inverseSlope2 = (x2-topX);
  if(y2-topY!=0) inverseSlope2 /= y2-topY;

  float from = topX, to = topX;
  //if topY is negative, it means the triangle begins outside the screen,
  //that being the case, the loop is started from y=1 to only render what
  //is on the screen
  int32_t startFrom = topY;
  if(topY < 0) {
    startFrom = 0;
    from += abs(topY)*inverseSlope1;
    to += abs(topY)*inverseSlope2;
  }
  //don't render past screen even if the triangle still goes on past it
  int32_t until = y2 > collorBuffer->height ? collorBuffer->height : y2;
  for(int32_t y=startFrom; y<=until; y++) {
    drawLineDDA(collorBuffer, from, y, to, y, argb8888);
    from += inverseSlope1;
    to += inverseSlope2;
  }
}
