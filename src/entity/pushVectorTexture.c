#include <stdlib.h>
#include <errno.h>

#include "entity.h"
#include "error.h"

void pushVectorTexture(struct entity *entity, struct vectorTextures vectorTextures) {
  if(entity->vectorsLength == 0) {
    entity->vectorTextures = malloc(sizeof(struct vectorTextures));
    if(entity->vectorTextures == NULL && errno == ENOMEM) errExit(1);
    entity->vectorsTextureLength = 1;
    entity->vectorTextures[0] = vectorTextures;
  } else {
    entity->vectorTextures = realloc(entity->vectorTextures, sizeof(struct vectorTextures)+entity->vectorsTextureLength*sizeof(struct vectorTextures));
    if(entity->vectorTextures == NULL && errno == ENOMEM) errExit(1);
    entity->vectorsTextureLength++;
    entity->vectorTextures[entity->vectorsTextureLength-1] = vectorTextures;
  }
}
