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

#include <errno.h>

#include <string.h>
#include <inttypes.h>

#include <SDL2/SDL_render.h>

#include "common.h"
#include "error.h"

struct collorBuffer *createCollorBuffer(SDL_Renderer *sdlRenderer, uint32_t windowWidth, uint32_t windowHeight) {
  struct collorBuffer *collorBuffer = malloc(sizeof(struct collorBuffer));
  if(collorBuffer == NULL && errno == ENOMEM) errExit(1);
  memset(collorBuffer, 0, sizeof(struct collorBuffer));

  collorBuffer->size = windowWidth*windowHeight;
  collorBuffer->width = windowWidth;
  collorBuffer->height = windowHeight;

  collorBuffer->buffer = malloc(sizeof(uint32_t)*(windowWidth*windowHeight));
  if(collorBuffer->buffer == NULL && errno == ENOMEM) errExit(1);
  memset(collorBuffer->buffer, 0, sizeof(uint32_t)*collorBuffer->size);

  collorBuffer->texture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, (int32_t)windowWidth, (int32_t)windowHeight);
  if(!collorBuffer->texture) errExit(5);

  return collorBuffer;
}
