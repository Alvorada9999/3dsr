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

#include <SDL2/SDL_video.h>
#include <errno.h>

#include <SDL2/SDL.h>
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "error.h"

struct SDL *initSdl(void) {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    errExit(2);
  };

  struct SDL *sdl = malloc(sizeof (struct SDL));
  if(sdl == NULL && errno == ENOMEM) errExit(1);
  memset(sdl, 0, sizeof(struct SDL));

  SDL_DisplayMode displayMode;
  if(SDL_GetCurrentDisplayMode(0, &displayMode) < 0) errExit(8);
  sdl->windowWidth = (uint32_t)displayMode.w;
  sdl->windowHeight = (uint32_t)displayMode.h;

  sdl->window = SDL_CreateWindow("3dsr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int32_t)sdl->windowWidth, (int32_t)sdl->windowHeight, SDL_WINDOW_FULLSCREEN);
  if(!sdl->window) errExit(3);

  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(!sdl->renderer) errExit(4);

  return sdl;
}
