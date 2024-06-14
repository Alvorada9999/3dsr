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

#include "common.h"

void drawPixel(struct collorBuffer *collorBuffer, int16_t x, int16_t y, uint32_t argb) {
  if(x >= 0 && x<collorBuffer->width && y>=0 && y<collorBuffer->height) {
    collorBuffer->buffer[collorBuffer->width*y+x] = argb;
  }
}
