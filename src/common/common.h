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

#ifndef _3DSR_COMMON
#define _3DSR_COMMON
#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#define TARGET_FPS 15
#define TARGET_FRAME_TIME 1000/TARGET_FPS

struct SDL {
  SDL_Window *window;
  SDL_Renderer *renderer;
  uint16_t windowWidth;
  uint16_t windowHeight;
};
struct collorBuffer {
  uint32_t *buffer;
  uint32_t size;
  SDL_Texture *texture;
  uint16_t width;
  uint16_t height;
};
#include "entity.h"

struct SDL *initSdl(void);
struct collorBuffer *createCollorBuffer(SDL_Renderer *sdlRenderer, uint32_t windowWidth, uint32_t windowHeight);
void clearCollorBuffer(struct collorBuffer *collorBuffer, uint32_t argb8888);
void renderCollorBuffer(struct collorBuffer *collorBuffer, SDL_Renderer *sdlRenderer);
void drawGrid(struct collorBuffer *collorBuffer, uint16_t dimension, uint32_t argb);
void drawRectangle(struct collorBuffer *collorBuffer, int16_t x, int16_t y, uint16_t width, uint16_t height, uint32_t argb);
void drawPixel(struct collorBuffer *collorBuffer, int16_t x, int16_t y, uint32_t argb);
void drawLineDDA(struct collorBuffer *collorBuffer, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t argb);

void render(struct SDL *sdl, struct collorBuffer *collorBuffer, struct entity *entities, uint32_t numberOfEntities);

bool shouldCull(struct entity entity, struct vector3D vertexA, struct vector3D vertexB, struct vector3D vertexC, struct vector3D camera);

void fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t argb8888);
void fillFlatBottom(int32_t topX, int32_t topY, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t argb8888);
void fillFlatTop(int32_t bottomX, int32_t bottomY, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t argb8888);
#endif // !_3DSR_COMMON
