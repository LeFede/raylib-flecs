#include "index.h"

void sy_PrepareCamera(ecs_iter_t *it) {
  si_Camera *c = ecs_field(it, si_Camera, 0);
  c->main.rotation = 0.0f;
  c->main.zoom = WINDOW_ZOOM;
  c->main.offset = (Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f};
  c->main.target = (Vector2){0.0f, 0.0f};
  c->zoomSpeed = 4.0f;
  c->rotateSpeed = 40.0f;
}
