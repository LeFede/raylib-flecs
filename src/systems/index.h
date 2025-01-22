#ifndef _SYSTEMS_
#define _SYSTEMS_
#include "../components/index.h"
#include "../constants.h"
#include <flecs.h>
#include <raylib.h>

void sy_HandleInput(ecs_iter_t *it);
void sy_PrepareCamera(ecs_iter_t *it);
void sy_DrawSprite(ecs_iter_t *it);
void sy_BeginDraw();
void sy_FinishDraw();

void setup(ecs_world_t *world);
void game_loop(ecs_world_t *world);
void cleanup(ecs_world_t *world);

void sy_DrawSprite(ecs_iter_t *it);
void sy_PrintDelta(ecs_iter_t *it);
void sy_SpawnEntities(ecs_iter_t *it);
void sy_UpdateCamera(ecs_iter_t *it);
void sy_LoadAssets(ecs_iter_t *it);

#endif
