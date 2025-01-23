#ifndef _CO_SPRITE_
#define _CO_SPRITE_

#include <flecs.h>
#include <raylib.h>

typedef struct {
  int idx;
  Vector2 origin;
  Color color;
} co_Sprite;


extern ECS_COMPONENT_DECLARE(co_Sprite);
#endif
