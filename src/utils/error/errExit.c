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

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void errExit(uint16_t errCode) {
  char *errors[10];

  errors[1] = "Not enough memory\n";

  errors[2] = "Failed to init video\n";
  errors[3] = "Failed to create window\n";
  errors[4] = "Failed to create sdl renderer\n";
  errors[5] = "Failed to create sdl texture\n";
  errors[6] = "Failed to update sdl texture\n";
  errors[7] = "Failed to copy a portion of a sdl texture\n";
  errors[8] = "Failed to get screen size\n";
  errors[9] = "Failed to open obj file\n";

  printf("\033[0m\033[H\033[0J\033[3J%s", errors[errCode]);
  exit(errCode);
}
