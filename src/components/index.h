#ifndef _CO_INDEX_
#define _CO_INDEX_
#include "../constants.h"
#include <raylib.h>

// Components =================================================================

typedef struct {
  int x, y;
} Position;

typedef struct {
  int idx;
  Vector2 origin;
  Color color;
} Sprite;

typedef struct {
  int x, y;
} Velocity;

// SINGLETONS =================================================================

typedef struct si_Assets {
  Texture2D textures[10];
} si_Assets;

typedef struct si_Camera {
  Camera2D main;
  float zoomSpeed;
  float rotateSpeed;
} si_Camera;

typedef struct si_Input {
  u32 a : 1, s : 1, d : 1, w : 1, space : 1, left_ctrl : 1, enter : 1, alt : 1,
      q : 1, e : 1;
} si_Input;

#endif
