#include "b.h"
#include "../main.h"
#include <stdio.h>

void b(int i)
{
  printf("b(%d) devuelve '%d'\n", i, b2(i));
}

static void init() __attribute__((constructor));

static void init() {
  register_plugin("b", &b);
}
