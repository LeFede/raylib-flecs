#ifndef _CO_POSITION_
#define _CO_POSITION_

#include <flecs.h>

typedef struct {
  int x, y;
} co_Position;

extern ECS_COMPONENT_DECLARE(co_Position);
#endif
