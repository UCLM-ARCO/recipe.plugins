#include <stdio.h>
#include <dlfcn.h>
#include <glib.h>
#include <gmodule.h>
#include "a.h"

#define RUTA_LIBB "./dirb/libb.so.1.0.0"


int main(){
  int i = 3;

  /* manejador de la libreria libb */
  GModule* pmodule;
  //void *pLibb;
  //void (*pFuncion)(int);
  void (*pFuncion)(int);

  /*  Se comprueba que el sistema soporta los plugins */
  if (!g_module_supported ())
    return 0;

  if(!(pmodule = g_module_open(RUTA_LIBB,G_MODULE_BIND_LAZY))){
    g_warning("No se pudo cargar la librería %s", RUTA_LIBB);
    return 1;
  }

  /*if ((pLibb = dlopen(RUTA_LIBB, RTLD_LAZY)) ==NULL) {
    fprintf(stderr, dlerror());
    return 1;
    }*/

  if(!(g_module_symbol(pmodule,"b", (gpointer*) &pFuncion))){
    g_warning("No se pudo cargar el simbolo: b");
    return 1;
  }
  /*if ((pFuncion = dlsym(pLibb, "b")) == NULL) {
    fprintf(stderr, dlerror());
    return 1;
    }*/

  printf("Provemos con %d\n",i);

  a(i);
  pFuncion(i);

  g_module_close(pmodule);
  //dlclose(pLibb);

  return(0);
}


