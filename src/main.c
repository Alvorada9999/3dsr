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

#include <stdlib.h>
#include <time.h>

#include <stdbool.h>
#include <stdint.h>

#include "common.h"
#include "input.h"

int32_t main(void) {
  struct SDL *sdl = initSdl();
  struct collorBuffer *collorBuffer = createCollorBuffer(sdl->renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

  bool isRunning = true;

  struct timespec time;
  time.tv_sec = 0;
  time.tv_nsec = 16666666;
  while(isRunning) {
    getInput();
    render(sdl, collorBuffer);
    nanosleep(&time, NULL);
  }
}
