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

void drawGrid(struct collorBuffer *collorBuffer, uint16_t dimension, uint32_t argb) {
  uint32_t currentRow = dimension;
  while(currentRow < collorBuffer->height) {
    for(uint16_t i=0; i<collorBuffer->width; i +=10) {
      collorBuffer->buffer[(collorBuffer->width*currentRow)+i] = argb;
    }
    currentRow += 10;
  }

  uint32_t currentColumn = dimension;
  while(currentColumn < collorBuffer->width) {
    for(uint16_t i=0; i<collorBuffer->height; i += 10) {
      collorBuffer->buffer[(i*collorBuffer->width)+currentColumn] = argb;
    }
    currentColumn += 10;
  }
}
