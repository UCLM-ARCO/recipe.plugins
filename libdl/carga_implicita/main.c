#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "a.h"

#ifndef PATH_MAX 
#define PATH_MAX 1024
#endif

struct plugin {
  char* key;
  void (*f)(int);
  struct plugin* next;
};

static struct plugin* plugins;

void
register_plugin (char* key, void (*f)(int))
{
  struct plugin* p = (struct plugin*) malloc(sizeof(struct plugin));
  p->next = plugins;
  p->f = f;
  p->key = key;
  plugins = p;
  printf("** Plugin '%s' registrado con éxito.\n", key);
}

void
unregister_plugin (char* key)
{
  struct plugin *prev = NULL, *p = plugins;
  while (p) {
    if (0==strcmp(p->key, key)) break;
    prev = p;
    p = p->next;
  }
  if (p) {
    if (prev) prev->next = p->next;
    else plugins = p->next;
    free(p);
  }
}

static struct plugin*
busca(char* key)
{
  struct plugin *p = plugins;
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

    sprintf(libname, "./dir%s/lib%s.so", key, key);
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

