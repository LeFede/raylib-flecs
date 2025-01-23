
#include "index.h"

void sy_DebugEntity(ecs_iter_t *it) {

  co_Position *p = ecs_field(it, co_Position, 0);
  const si_Camera *c = ecs_singleton_get(it->world, si_Camera);

  BeginMode2D(c->main);

  for (int i = 0; i < it->count; i++) {
    DrawRectangle(p[i].x, p[i].y, 1, 1, (Color){255, 0, 0, 255});
  }

  EndMode2D();
}
