#include "test.h"
#include "a.h"
#include <stdio.h>

void 
b(int i) {
	printf("Estoy en B (%d)\n", i);
	a(i+1);
}

static void init() __attribute__((constructor));

static void init() {
  register_plugin("b", &b);
}
