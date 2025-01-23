#ifndef _CO_DEBUG_
#define _CO_DEBUG_

#include <flecs.h>

typedef struct {
  int x;
} co_Debug;

extern ECS_COMPONENT_DECLARE(co_Debug);
#endif
