#ifndef _SI_CAMERA_
#define _SI_CAMERA_

#include <flecs.h>
#include <raylib.h>

typedef struct si_Camera {
  Camera2D main;
  float zoomSpeed;
  float rotateSpeed;
} si_Camera;


extern ECS_COMPONENT_DECLARE(si_Camera);
#endif
