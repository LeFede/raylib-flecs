#ifndef _SI_ASSETS_
#define _SI_ASSETS_

#include <flecs.h>
#include <raylib.h>

typedef struct si_Assets {
  Texture2D textures[10];
} si_Assets;


extern ECS_COMPONENT_DECLARE(si_Assets);
#endif
