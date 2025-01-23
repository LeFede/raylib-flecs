#include "index.h"
#include <flecs/addons/flecs_c.h>
#include <stdbool.h>

void spawn_grid(ecs_world_t *world) {
  ecs_entity_t e;
  co_Position p = {.x = 0, .y = 0};
  co_Sprite s = {.idx = t_GRID,
                 .origin = (Vector2){0, 0},
                 .color = (Color){255, 255, 255, 50}};
  e = ecs_new(world);
  ecs_set(world, e, co_Position, {.x = p.x, .y = p.y});
  ecs_set(world, e, co_Sprite,
          {.idx = s.idx, .origin = s.origin, .color = s.color});
  printf("Grid spawned\n");
}

void spawn_aseprite(ecs_world_t *world, int x, int y) {

  ecs_entity_t e;
  co_Position p = {.x = x, .y = y};
  // Velocity v = {.x = -(4 + ((sin(i * 1.f)) * 100)),
  //               .y = 1 + cos(i * 0.1f) * 100};
  // Sprite s = {(sin(i * 0.1f) * 128 + 128), (cos(i * 0.1f) * 128 + 128),
  //             (sin(i * 0.2f) * 128 + 128)};
  co_Sprite s = {.idx = t_ASEPRITE,
                 .origin = (Vector2){7, 15},
                 .color = (Color){255, 255, 255, 255}};

  e = ecs_new(world);
  ecs_set(world, e, co_Position, {p.x, p.y});
  ecs_set(world, e, co_Sprite, {s.idx, s.origin, s.color});
  ecs_set(world, e, co_Debug, {});

  printf("Aseprite spawned\n");
  ecs_enable_component(world, e, co_Sprite, false);
}

void sy_SpawnEntities(ecs_iter_t *it) {
  spawn_grid(it->world);
  spawn_aseprite(it->world, 30, 40);
  spawn_aseprite(it->world, 100, 40);
}
