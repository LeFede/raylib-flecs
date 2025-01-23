#include "index.h"
#include <flecs/addons/flecs_c.h>

void sy_UpdateCamera(ecs_iter_t *it) {
  si_Camera *c = ecs_field(it, si_Camera, 0);
  const si_Input *input = ecs_singleton_get(it->world, si_Input);

  c->main.zoom += c->zoomSpeed * GetFrameTime() * (input->w - input->s);
  c->main.rotation += c->rotateSpeed * GetFrameTime() * (input->a - input->d);
}
