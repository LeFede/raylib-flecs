#include "index.h"

void sy_HandleInput(ecs_iter_t *it) {
  si_Input *input = ecs_field(it, si_Input, 0);

  input->a = IsKeyDown(KEY_A);
  input->s = IsKeyDown(KEY_S);
  input->d = IsKeyDown(KEY_D);
  input->w = IsKeyDown(KEY_W);
  input->space = IsKeyDown(KEY_SPACE);
  input->left_ctrl = IsKeyDown(KEY_LEFT_CONTROL);
  input->enter = IsKeyDown(KEY_ENTER);
  input->alt = IsKeyDown(KEY_LEFT_ALT);
  input->q = IsKeyDown(KEY_Q);
  input->e = IsKeyDown(KEY_E);
}
