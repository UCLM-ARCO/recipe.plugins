#include "a.h"
#include <stdio.h>

void a(int i)
{
  printf("Numerito es: %d\n", a2(i));
}

static void init() __attribute__((constructor));

static void init() {
  register_plugin("a", &a);
}
