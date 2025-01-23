#include "index.h"

void sy_LoadAssets(ecs_iter_t *it) {
  si_Assets *a = ecs_field(it, si_Assets, 0);

  a->textures[t_GRID] = LoadTexture("assets/grid.png");
  a->textures[t_ASEPRITE] = LoadTexture("assets/aseprite.png");
}
