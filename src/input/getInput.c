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

#include <SDL2/SDL_events.h>

#include "common.h"

extern uint8_t renderOption;
void getInput(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
    case SDL_QUIT:
      exit(1);
      break;
    case SDL_KEYDOWN:
      if(event.key.keysym.sym == SDLK_1) {
        renderOption = RENDER_OPTION_ONLY_VECTORS;
      }
      if(event.key.keysym.sym == SDLK_2) {
        renderOption = RENDER_OPTION_ONLY_WIREFRAME;
      }
      if(event.key.keysym.sym == SDLK_3) {
        renderOption = RENDER_OPTION_ONLY_FACES;
      }
      if(event.key.keysym.sym == SDLK_4) {
        renderOption = RENDER_OPTION_WIREFRAME_AND_FACES;
      }
      break;
    default:
      break;
  }
}
