#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <gmodule.h>
#include <glib/ghash.h>
#include "a.h"

#ifndef PATH_MAX 
#define PATH_MAX 1024
#endif


static GHashTable* plugins = NULL;

void
register_plugin (char* key, void (*f)(int))
{
  if (plugins == NULL)
    plugins = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
  g_hash_table_insert(plugins, key, f);
  printf("** Plugin '%s' registrado con éxito.\n", key);
}

void
unregister_plugin (char* key)
{
  if (plugins != NULL)
    g_hash_table_remove(plugins, key);
  
}

void
f (char* key, int i)
{
  GModule* pmodule;
  void (*p)(int) = NULL;

  if (plugins != NULL)
    p = g_hash_table_lookup(plugins, key);

  if (!p) {
    char libname[PATH_MAX];

    sprintf(libname, "./dir%s/lib%s.so", key, key);
    printf("Intentando cargar '%s'.\n", libname);
    if((pmodule = g_module_open(libname,G_MODULE_BIND_LAZY))==NULL){
      g_warning("No se pudo cargar la librería %s", libname);
      exit(1);
    }

    if (plugins != NULL)
      p = g_hash_table_lookup(plugins, key);
  }

  if (p) p(i);
  else
     fprintf(stderr, "ERROR: El plugin '%s' no está disponible.\n", key);
}

int
main()
{
  int i = 3;
  
  printf("Resultados para '%d'.\n",i);

  a(i);      // llamada estática.
  f("b",i);  // llamada a plugin.

  return 0;
}


