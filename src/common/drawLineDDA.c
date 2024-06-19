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
#include "math.h"

void drawLineDDA(struct collorBuffer *collorBuffer, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t argb) {
  int32_t deltaX = x2-x1, deltaY = y2-y1;
  int32_t biggestSideLenght = abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY);

  float xIncrement = deltaX/(float)biggestSideLenght;
  float yIncrement = deltaY/(float)biggestSideLenght;

  float currentX = x1, currentY = y1;

  for(int32_t i=0; i<=biggestSideLenght; i++) {
    drawPixel(collorBuffer, round(currentX), round(currentY), argb);
    currentX += xIncrement;
    currentY += yIncrement;
  }
}
