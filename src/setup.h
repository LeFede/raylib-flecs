#ifndef _SETUP_
#define _SETUP_
#include <flecs.h>

void setup(ecs_world_t *world);
void game_loop(ecs_world_t *world);
void cleanup(ecs_world_t *world);
void spawn_grid(ecs_world_t *world);
// void sy_SpawnEntities(ecs_iter_t *it);

#endif
