#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

#include "entity.h"
#include "error.h"

struct vectorTextureUvCoordinates* addNewUV(uint32_t *length, struct vectorTextureUvCoordinates *array, struct vectorTextureUvCoordinates vectorTexture) {
  if(*length == 0) {
    array = malloc(sizeof(struct vectorTextureUvCoordinates));
    if(array == NULL && errno == ENOMEM) errExit(1);
    *length = 1;
    array[0] = vectorTexture;
  } else {
    array = realloc(array, sizeof(struct vectorTextureUvCoordinates)+(*length)*sizeof(struct vectorTextureUvCoordinates));
    if(array == NULL && errno == ENOMEM) errExit(1);
    (*length)++;
    array[*length-1] = vectorTexture;
  }
  return array;
}
