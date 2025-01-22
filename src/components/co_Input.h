#ifndef _CO_INPUT_
#define _CO_INPUT_
#include "../constants.h"

typedef struct Input {
  u32 a : 1, s : 1, d : 1, w : 1, space : 1, left_ctrl : 1, enter : 1, alt : 1,
      q : 1, e : 1;
} Input;

#endif
