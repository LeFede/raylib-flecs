#include "./systems/index.h"
#include "constants.h"
#include <flecs.h>
#include <raylib.h>

void setup(ecs_world_t *world) {

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(WINDOW_FPS);

  // Components
  ECS_COMPONENT_DEFINE(world, co_Position);
  ECS_COMPONENT_DEFINE(world, co_Sprite);
  ecs_add_id(world, ecs_id(co_Sprite), EcsCanToggle);
  ECS_COMPONENT_DEFINE(world, co_Velocity);
  ECS_COMPONENT_DEFINE(world, co_Debug);

  ECS_COMPONENT_DEFINE(world, si_Input);
  ECS_COMPONENT_DEFINE(world, si_Camera);
  ECS_COMPONENT_DEFINE(world, si_Assets);

  // Singletons
  ecs_singleton_set(world, si_Input, {});
  ecs_singleton_set(world, si_Camera, {});
  ecs_singleton_set(world, si_Assets, {});

  // Start
  ECS_SYSTEM(world, sy_SpawnEntities, EcsOnStart);
  ECS_SYSTEM(world, sy_LoadAssets, EcsOnStart, si_Assets);
  ECS_SYSTEM(world, sy_PrepareCamera, EcsOnStart, si_Camera);

  // INPUT 🎹 =================================================================
  ECS_SYSTEM(world, sy_HandleInput, EcsOnUpdate, si_Input);

  // UPDATE START ⬆️  ==========================================================
  ECS_SYSTEM(world, sy_UpdateCamera, EcsOnUpdate, si_Camera);

  // UPDATE ➡️  ================================================================
  // UPDATE END ⬇️  ============================================================

  // DRAW 🖌️ ==================================================================
  ECS_SYSTEM(world, sy_BeginDraw, EcsOnUpdate, 0);
  ECS_SYSTEM(world, sy_DebugEntity, EcsOnUpdate, co_Position, co_Debug);
  ECS_SYSTEM(world, sy_DrawSprite, EcsOnUpdate, co_Position, co_Sprite);
  ECS_SYSTEM(world, sy_PrintDelta, EcsOnUpdate, 0);
  ECS_SYSTEM(world, sy_FinishDraw, EcsOnUpdate, 0);

  // other...
  // Spawners.s[0] =
  //     ecs_system(world, {.entity = ecs_entity(world,
  //                                             {
  //                                                 .name = "sy_SpawnEntities",
  //                                             }),
  //                        .callback = sy_SpawnEntities});

  // ecs_run(world, Spawners.s[0], 0.0f, NULL);
  // ecs_enable(Game.world, sy_PrintDelta, true);
}

void game_loop(ecs_world_t *world) {
  float delta_time;

  while (!WindowShouldClose()) {
    delta_time = GetFrameTime();
    ecs_progress(world, delta_time);
  }
}

void cleanup(ecs_world_t *world) {
  ecs_fini(world);
  CloseWindow();
}
