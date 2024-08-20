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

#include <SDL2/SDL_render.h>

#include "common.h"
#include "error.h"

void renderCollorBuffer(struct collorBuffer *collorBuffer, SDL_Renderer *sdlRenderer) {
  if(SDL_UpdateTexture(collorBuffer->texture, NULL, collorBuffer->buffer, (int32_t)(sizeof(uint32_t)*collorBuffer->width)) < 0) errExit(6);
  if(SDL_RenderCopy(sdlRenderer, collorBuffer->texture, NULL, NULL) < 0) errExit(7);
}
