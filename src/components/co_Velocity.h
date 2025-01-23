#ifndef _CO_VELOCITY_
#define _CO_VELOCITY_

#include <flecs.h>

typedef struct {
  int x, y;
} co_Velocity;


extern ECS_COMPONENT_DECLARE(co_Velocity);
#endif
