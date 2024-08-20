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
#include "utils.h"

extern struct collorBuffer *collorBuffer;

void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t argb8888) {
  if(y0 > y1) {
    swap(&y0, &y1);
    swap(&x0, &x1);
  }
  if(y1 > y2) {
    swap(&y1, &y2);
    swap(&x1, &x2);
  }
  if(y0 > y1) {
    swap(&y0, &y1);
    swap(&x0, &x1);
  }

  //getting triangle midpoint
  //My = y1
  int32_t Mx = ((x2-x0)*(y1-y0));
  if(y2-y0 > 0) Mx /= y2-y0;
  Mx += x0;

  if(y1 == y2) {
    fillFlatBottom(x0, y0, x1, y1, x2, y2, argb8888);
  } else {
    fillFlatBottom(x0, y0, Mx, y1, x1, y1, argb8888);
  }

  if(y0 == y1) {
    fillFlatTop(x2, y2, x1, y1, x0, y0, argb8888);
  } else {
    fillFlatTop(x2, y2, Mx, y1, x1, y1, argb8888);
  }
}
