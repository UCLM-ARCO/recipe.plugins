#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <gmodule.h>
#include <glib/ghash.h>

static GHashTable* plugin = NULL;

void
register_plugin (char* key, void (*f)(int))
{
 if (plugin == NULL)
    plugin = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
 g_hash_table_insert(plugin,key,f);
 printf("** Registrado %s\n", key);
}

void
unregister_plugin (char* key)
{
  if (plugin != NULL)
    g_hash_table_remove(plugin,key);
  
}

void
f (char* key, int i)
{
  GModule* pmodule;
  void (*p)(int);

  p = g_hash_table_lookup(plugin, key);
  if (!p) {
    char nombre[1024];
    sprintf(nombre, "./dir%s/lib%s.so", key,key);
    if((pmodule = g_module_open(nombre,G_MODULE_BIND_LAZY))==NULL){
      g_warning("No se pudo cargar la librería %s", nombre);
      exit(1);
    }
    p = g_hash_table_lookup(plugin, key);
  }
  if (p) p(i);
}

int
main()
{
  int i = 3;
  
  printf("Provemos con %d\n",i);

  f("a",3);
  f("b",3);
  return 0;
}


