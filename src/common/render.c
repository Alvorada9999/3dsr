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

#include <SDL2/SDL_render.h>

#include "common.h"
#include "entity.h"

void render(struct SDL *sdl, struct collorBuffer *collorBuffer, struct entity *entities, uint32_t numberOfEntities) {
  drawGrid(collorBuffer, 10, 0xFF00B300);
  for(uint32_t i=0; i<numberOfEntities; i++) {
    drawEntity(collorBuffer, entities[i]);
  }
  renderCollorBuffer(collorBuffer, sdl->renderer);
  clearCollorBuffer(collorBuffer, 0x00000009);
  SDL_RenderPresent(sdl->renderer);
}
