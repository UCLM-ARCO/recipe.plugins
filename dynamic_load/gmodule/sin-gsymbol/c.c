#include "test.h"
#include <stdio.h>

void 
c(int i) {
	printf("Estoy en C (%d)\n", i);
}

static void init() __attribute__((constructor));

static void init() {
  register_plugin("c", &c);
}
