#include "test.h"
#include <stdio.h>

void 
a(int i) {
	printf("Estoy en A (%d)\n", i);
}

static void init() __attribute__((constructor));

static void init() {
  register_plugin("a", &a);
}
