#include <SDL2/SDL_image.h>

#include <stdlib.h>

#include "common.h"

struct argb8888Buffer loadImageToArgb8888(const char *filename) {
  struct argb8888Buffer buffer = {.height = 0, .width = 0, .pixelArray = NULL};

  // loads the png image into a sdl surface
  SDL_Surface *tempSurface = IMG_Load(filename);
  if (!tempSurface)
    return buffer;

  // converts to argb8888
  SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(tempSurface, SDL_PIXELFORMAT_ARGB8888, 0);
  // frees the original
  SDL_FreeSurface(tempSurface);

  if (!formattedSurface) return buffer;

  buffer.width = formattedSurface->w;
  buffer.height = formattedSurface->h;

  size_t pixelCount = buffer.width * buffer.height;
  buffer.pixelArray = (uint32_t *)malloc(pixelCount * sizeof(uint32_t));

  if (buffer.pixelArray) {
    if (SDL_MUSTLOCK(formattedSurface)) {
      // blocks the surface if needed for directs access (mostly optional for software surfaces) https://wiki.libsdl.org/SDL2/SDL_LockSurface
      SDL_LockSurface(formattedSurface);
      // copy the pixels, pitch handles the memory alignment per line
      memcpy(buffer.pixelArray, formattedSurface->pixels, pixelCount * sizeof(uint32_t));

      SDL_UnlockSurface(formattedSurface);
    }
  }
  SDL_FreeSurface(formattedSurface);
  return buffer;
}