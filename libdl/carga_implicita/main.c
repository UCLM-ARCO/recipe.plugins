#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <stdio.h>
#include "a.h"

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
  printf("** Registrado %s\n", key);
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
  
  if(p == protos)
    printf("No se ha encontrado el plugin %s\n",key);
  return p;
}

void
f (char* key, int i)
{
  struct plugin* p;
  p = busca(key);
  if (!p) {
    char nombre[1024];
    sprintf(nombre, "./dir%s/lib%s.so", key, key);
    dlopen(nombre, RTLD_LAZY);
    p = busca(key);
  }
  if (p) p->f(i);
}

int
main()
{
  int i = 3;
  
  printf("Probemos con %d\n",i);

  a(i);      // Llamada estática.
  f("b",i);  // Llamada plugin.
  return 0;
}


