#include "setup.h"
#include <flecs.h>
#include <raylib.h>
#include <stdbool.h>

int main() {
  ecs_world_t *world = ecs_init();
  setup(world);
  game_loop(world);
  cleanup(world);
  return 0;
}
