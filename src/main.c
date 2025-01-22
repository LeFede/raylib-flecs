#include "components/index.h"
#include "constants.h"
#include "systems/index.h"
#include <flecs.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Sprite);
ECS_COMPONENT_DECLARE(Velocity);
ECS_COMPONENT_DECLARE(si_Assets);
ECS_COMPONENT_DECLARE(si_Systems);
ECS_COMPONENT_DECLARE(si_Camera);
ECS_COMPONENT_DECLARE(si_Input);

void setup(ecs_world_t *world);
void game_loop(ecs_world_t *world);
void cleanup(ecs_world_t *world);

void sy_DrawSprite(ecs_iter_t *it);
void sy_PrintDelta(ecs_iter_t *it);
void sy_SpawnEntities(ecs_iter_t *it);
void sy_UpdateCamera(ecs_iter_t *it);
void sy_LoadAssets(ecs_iter_t *it);

int main() {
  ecs_world_t *world = ecs_init();
  setup(world);
  game_loop(world);
  cleanup(world);
  return 0;
}

inline void game_loop(ecs_world_t *world) {
  float delta_time;

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();
    ecs_progress(world, delta_time);
  }
}

inline void cleanup(ecs_world_t *world) {
  ecs_fini(world);
  CloseWindow();
}

void spawn_grid(ecs_world_t *world) {
  ecs_entity_t e;
  Position p = {.x = 0, .y = 0};
  Sprite s = {.idx = t_GRID,
              .origin = (Vector2){0, 0},
              .color = (Color){255, 255, 255, 50}};
  e = ecs_new(world);
  ecs_set(world, e, Position, {.x = p.x, .y = p.y});
  ecs_set(world, e, Sprite,
          {.idx = s.idx, .origin = s.origin, .color = s.color});
}

void spawn_aseprite(ecs_world_t *world, int x, int y) {

  ecs_entity_t e;
  Position p = {.x = x, .y = y};
  // Velocity v = {.x = -(4 + ((sin(i * 1.f)) * 100)),
  //               .y = 1 + cos(i * 0.1f) * 100};
  // Sprite s = {(sin(i * 0.1f) * 128 + 128), (cos(i * 0.1f) * 128 + 128),
  //             (sin(i * 0.2f) * 128 + 128)};
  Sprite s = {.idx = t_ASEPRITE,
              .origin = (Vector2){7, 15},
              .color = (Color){255, 255, 255, 255}};
  e = ecs_new(world);
  ecs_set(world, e, Position, {.x = p.x, .y = p.y});
  ecs_set(world, e, Sprite,
          {.idx = s.idx, .origin = s.origin, .color = s.color});
  printf("Aseprite spawned!\n");
}

struct Spawners {
  ecs_entity_t s[10];
} Spawners;

typedef struct si_Systems {
  ecs_entity_t spawners[10];
} si_Systems;

void setup(ecs_world_t *world) {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(WINDOW_FPS);

  // Components
  ECS_COMPONENT_DEFINE(world, Position);
  ECS_COMPONENT_DEFINE(world, Sprite);
  ECS_COMPONENT_DEFINE(world, Velocity);
  ECS_COMPONENT_DEFINE(world, si_Input);
  ECS_COMPONENT_DEFINE(world, si_Camera);
  ECS_COMPONENT_DEFINE(world, si_Assets);
  ECS_COMPONENT_DEFINE(world, si_Systems);

  // Singletons
  ecs_singleton_set(world, si_Input, {});
  ecs_singleton_set(world, si_Camera, {});
  ecs_singleton_set(world, si_Assets, {});
  ecs_singleton_set(world, si_Systems, {});

  // Start
  // ECS_SYSTEM(world, sy_SpawnEntities, EcsOnStart);
  ECS_SYSTEM(world, sy_LoadAssets, EcsOnStart, si_Assets);
  ECS_SYSTEM(world, sy_PrepareCamera, EcsOnStart, si_Camera);

  // UpdateStart
  ECS_SYSTEM(world, sy_HandleInput, EcsOnUpdate, si_Input);

  // Update
  ECS_SYSTEM(world, sy_UpdateCamera, EcsOnUpdate, si_Camera);

  // UpdateEnd
  ECS_SYSTEM(world, sy_BeginDraw, EcsOnUpdate, 0);
  ECS_SYSTEM(world, sy_DrawSprite, EcsOnUpdate, Position, Sprite);
  ECS_SYSTEM(world, sy_PrintDelta, EcsOnUpdate, 0);
  ECS_SYSTEM(world, sy_FinishDraw, EcsOnUpdate, 0);

  // other...
  Spawners.s[0] =
      ecs_system(world, {.entity = ecs_entity(world,
                                              {
                                                  .name = "sy_SpawnEntities",
                                              }),
                         .callback = sy_SpawnEntities});

  ecs_run(world, Spawners.s[0], 0.0f, NULL);
  // ecs_enable(Game.world, sy_PrintDelta, true);
}

void sy_LoadAssets(ecs_iter_t *it) {
  si_Assets *a = ecs_field(it, si_Assets, 0);

  a->textures[t_GRID] = LoadTexture("assets/grid.png");
  a->textures[t_ASEPRITE] = LoadTexture("assets/aseprite.png");
}

void sy_UpdateCamera(ecs_iter_t *it) {
  si_Camera *c = ecs_field(it, si_Camera, 0);
  const si_Input *input = ecs_singleton_get(it->world, si_Input);

  c->main.zoom += c->zoomSpeed * GetFrameTime() * (input->w - input->s);
  c->main.rotation += c->rotateSpeed * GetFrameTime() * (input->a - input->d);
}

void sy_SpawnEntities(ecs_iter_t *it) {
  spawn_grid(it->world);
  spawn_aseprite(it->world, 30, 40);
  spawn_aseprite(it->world, 100, 40);
}

void sy_PrintDelta(ecs_iter_t *it) {
  const si_Camera *c = ecs_singleton_get(it->world, si_Camera);
  const si_Input *input = ecs_singleton_get(it->world, si_Input);
  const int fps_number = GetFPS();

  DrawRectangle(0, 0, 250, 600, (Color){20, 20, 20, 50});
  DrawText(TextFormat("Delta: %f\n", it->delta_time), 20, 20, 25,
           (Color){255, 255, 255, 255});
  DrawText(TextFormat("Fps: %d\n", fps_number), 20, 45, 25,
           (Color){255, 255, 255, 255});
  DrawText(TextFormat("Zoom: %.2f\n", c->main.zoom), 20, 80, 25,
           (Color){255, 255, 255, 255});
  DrawText(TextFormat("Rotation: %.2f\n", c->main.rotation), 20, 105, 25,
           (Color){255, 255, 255, 255});
  DrawText(TextFormat("Q:%d\nE:%d\nW:%d\nA:%d\nS:%d\nD:%d\nCTRL:%d\nSPACE:%"
                      "d\nENTER:%d\nALT:%d",
                      input->q, input->e, input->w, input->a, input->s,
                      input->d, input->left_ctrl, input->space, input->enter,
                      input->alt),
           20, 160, 25, (Color){255, 255, 255, 255});
  DrawLine(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2,
           (Color){0, 255, 0, 100});
  DrawLine(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT,
           (Color){0, 255, 0, 100});
}

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
