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
  gpointer (*pFuncion)(int);

  if((pmodule = g_module_open(RUTA_LIBB,G_MODULE_BIND_LAZY))==NULL){
    g_warning("No se pudo cargar la librería %s", RUTA_LIBB);
    return 1;
  }


  if(!(g_module_symbol(pmodule,"b", (gpointer*)&pFuncion))){
    g_warning("No se pudo cargar el simbolo: b");
    return 1;
  }
 
  printf("**Provemos con %d\n",i);

  a(i);
  pFuncion(i);

  g_module_close(pmodule);
 
  return(0);
}


