#include "constants.h"
#include <flecs.h>
#include <raylib.h>

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
