#include "index.h"

void sy_DrawSprite(ecs_iter_t *it) {
  const si_Camera *c = ecs_singleton_get(it->world, si_Camera);
  const si_Assets *a = ecs_singleton_get(it->world, si_Assets);

  BeginMode2D(c->main);

  Position *p = ecs_field(it, Position, 0);
  Sprite *s = ecs_field(it, Sprite, 1);
  for (int i = 0; i < it->count; i++) {
    DrawTexture(a->textures[s[i].idx], p[i].x - s[i].origin.x,
                p[i].y - s[i].origin.y, s[i].color);
    DrawRectangle(p[i].x, p[i].y, 1, 1, (Color){255, 0, 0, 255});
  }

  EndMode2D();
}
