#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "a.h"

#define PLUGIN_PATH "/home/dvilla/repos/public/misc/plugins/libdl/carga_implicita"
#define PATH_MAX 1024

struct plugin {
  char* key;
  void (*f)(int);
  struct plugin* next;
};

static struct plugin* protos;

void
register_plugin (char* key, void (*f)(int))
{
  struct plugin* p = (struct plugin*) malloc(sizeof(struct plugin));
  p->next = protos;
  p->f = f;
  p->key = key;
  protos = p;
  printf("** Plugin '%s' registrado con éxito.\n", key);
}

void
unregister_plugin (char* key)
{
  struct plugin *prev = NULL, *p = protos;
  while (p) {
    if (0==strcmp(p->key, key)) break;
    prev = p;
    p = p->next;
  }
  if (p) {
    if (prev) prev->next = p->next;
    else protos = p->next;
    free(p);
  }
}

static struct plugin*
busca(char* key)
{
  struct plugin *p = protos;
  while (p) {
    if (0==strcmp(p->key, key)) break;
    p = p->next;
  }
  return p;
}

void
f (char* key, int i)
{
  struct plugin* p;
  p = busca(key);
  if (!p) {
    char libname[PATH_MAX];
    char path[PATH_MAX];

    sprintf(libname, "%s/dir%s/lib%s.so", getcwd(path, PATH_MAX), key, key);
    printf("Intentando cargar '%s'.\n", libname);
    dlopen(libname, RTLD_LAZY);

    p = busca(key);
  }
  if (p) p->f(i);
  else 
    fprintf(stderr, "ERROR: El plugin '%s' no está disponible.\n", key);
}

int
main()
{
  int i = 3;
  
  printf("Resultados para '%d'.\n",i);

  a(i);      // Llamada estática.
  f("b",i);  // Llamada a plugin.

  return 0;
}

