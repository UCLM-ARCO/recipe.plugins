#include <stdio.h>
#include <dlfcn.h>
#include "a.h"

#define RUTA_LIBB "./dirb/libb.so.1.0.0"


int main(){
  int i = 3;

  /* manejador de la libreria libb */
  void *pLibb;
  void (*pFuncion)(int);

  if ((pLibb = dlopen(RUTA_LIBB, RTLD_LAZY)) ==NULL) {
    fprintf(stderr, dlerror());
    return 1;
  }

  if ((pFuncion = dlsym(pLibb, "b")) == NULL) {
    fprintf(stderr, dlerror());
    return 1;
  }

  printf("Provemos con %d\n",i);

  a(i);
  pFuncion(i);

  dlclose(pLibb);

  return(0);
}


