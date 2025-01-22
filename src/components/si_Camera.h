#ifndef _SI_CAMERA_
#define _SI_CAMERA_
#include <raylib.h>

typedef struct si_Camera {
  Camera2D main;
  float zoomSpeed;
  float rotateSpeed;
} si_Camera;

#endif
