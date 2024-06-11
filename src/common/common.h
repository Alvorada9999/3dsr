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

#ifndef _3DSR_COMMON
#define _3DSR_COMMON
#include <SDL2/SDL.h>

// #define WINDOW_WIDTH 800
// #define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 300

struct SDL {
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint32_t windowWidth;
  uint32_t windowHeight;
};
struct collorBuffer {
  uint32_t *buffer;
  uint32_t size;
  SDL_Texture *texture;
};

struct SDL *initSdl(void);
void render(struct SDL *sdl, struct collorBuffer *collorBuffer);
struct collorBuffer *createCollorBuffer(SDL_Renderer *sdlRenderer, uint32_t windowWidth, uint32_t windowHeight);
void clearCollorBuffer(struct collorBuffer *collorBuffer, uint32_t argb8888);
void renderCollorBuffer(struct collorBuffer *collorBuffer, SDL_Renderer *sdlRenderer, uint32_t windowWidth);

#endif // !_3DSR_COMMON
