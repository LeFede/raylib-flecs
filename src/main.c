#include "components/co_Input.h"
#include "components/index.h"
#include "constants.h"
#include "systems/sy_HandleInput.h"
#include <flecs.h>
#include <flecs/addons/flecs_c.h>
#include <flecs/private/addons.h>
#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Sprite);
ECS_COMPONENT_DECLARE(Velocity);
ECS_COMPONENT_DECLARE(Input);
ECS_COMPONENT_DECLARE(si_Camera);

typedef struct si_Camera {
  Camera2D main;
  float zoomSpeed;
  float rotateSpeed;
} si_Camera;

void setup(ecs_world_t *world);
void game_loop(ecs_world_t *world);
void cleanup(ecs_world_t *world);

void sy_DrawSprite(ecs_iter_t *it);
void sy_PrintDelta(ecs_iter_t *it);
void sy_FinishDraw(ecs_iter_t *it);
void sy_SpawnEntities(ecs_iter_t *it);
void sy_BeginDraw(ecs_iter_t *it);
void sy_UpdateCamera(ecs_iter_t *it);

struct Assets {
  Texture2D textures[10];
} Assets;

enum Tex { t_GRID, t_ASEPRITE };

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

inline void setup(ecs_world_t *world) {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(WINDOW_FPS);

  Assets.textures[t_GRID] = LoadTexture("assets/grid.png");
  Assets.textures[t_ASEPRITE] = LoadTexture("assets/aseprite.png");

  ECS_COMPONENT_DEFINE(world, Position);
  ECS_COMPONENT_DEFINE(world, Sprite);
  ECS_COMPONENT_DEFINE(world, Velocity);
  ECS_COMPONENT_DEFINE(world, Input);
  ECS_COMPONENT_DEFINE(world, si_Camera);

  ecs_singleton_set(world, Input, {});
  ecs_singleton_set(
      world, si_Camera,
      {
          .main.rotation = 0.0f,
          .main.zoom = WINDOW_ZOOM,
          .main.offset = (Vector2){WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f},
          .main.target = (Vector2){0.0f, 0.0f},
          .zoomSpeed = 4.0f,
          .rotateSpeed = 40.0f,
      });

  // Start
  ECS_SYSTEM(world, sy_SpawnEntities, EcsOnStart);
  // UpdateStart
  ECS_SYSTEM(world, sy_HandleInput, EcsOnUpdate, Input);
  // Update
  ECS_SYSTEM(world, sy_UpdateCamera, EcsOnUpdate, si_Camera);
  // UpdateEnd
  ECS_SYSTEM(world, sy_BeginDraw, EcsOnUpdate, 0);
  ECS_SYSTEM(world, sy_DrawSprite, EcsOnUpdate, Position, Sprite);
  ECS_SYSTEM(world, sy_PrintDelta, EcsOnUpdate, 0);
  ECS_SYSTEM(world, sy_FinishDraw, EcsOnUpdate, 0);

  // ecs_enable(Game.world, sy_PrintDelta, true);
}

void sy_UpdateCamera(ecs_iter_t *it) {
  si_Camera *c = ecs_field(it, si_Camera, 0);
  const Input *input = ecs_singleton_get(it->world, Input);

  c->main.zoom += c->zoomSpeed * GetFrameTime() * (input->w - input->s);
  c->main.rotation += c->rotateSpeed * GetFrameTime() * (input->a - input->d);
}

void sy_BeginDraw(ecs_iter_t *it) {
  BeginDrawing();
  ClearBackground(WINDOW_BACKGROUND);
}

void sy_SpawnEntities(ecs_iter_t *it) {
  spawn_grid(it->world);
  spawn_aseprite(it->world, 30, 40);
  spawn_aseprite(it->world, 100, 40);
}

void sy_FinishDraw(ecs_iter_t *it) { EndDrawing(); }

void sy_PrintDelta(ecs_iter_t *it) {
  const si_Camera *c = ecs_singleton_get(it->world, si_Camera);
  const int fps_number = GetFPS();
  const Input *input = ecs_singleton_get(it->world, Input);

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

  BeginMode2D(c->main);

  Position *p = ecs_field(it, Position, 0);
  Sprite *s = ecs_field(it, Sprite, 1);
  for (int i = 0; i < it->count; i++) {
    DrawTexture(Assets.textures[s[i].idx], p[i].x - s[i].origin.x,
                p[i].y - s[i].origin.y, s[i].color);
    DrawRectangle(p[i].x, p[i].y, 1, 1, (Color){255, 0, 0, 255});
  }

  EndMode2D();
}

// Queries.it = ecs_query_iter(Game.world, Queries.position_sprite);
// while (ecs_query_next(&Queries.it)) {
//   Position *p = ecs_field(&Queries.it, Position, 0);
//   Sprite *s = ecs_field(&Queries.it, Sprite, 1);
//   for (int i = 0; i < Queries.it.count; i++) {
//     DrawTexture(Assets.textures[s[i].idx], p[i].x - s[i].origin.x,
//                 p[i].y - s[i].origin.y, s[i].color);
//     DrawRectangle(p[i].x, p[i].y, 1, 1, (Color){255, 0, 0, 255});
//   }
// }
