#
# -fPIC indica que se debe generar código independiente de la posicion
# -shared indica que será un objeto compartido -> shared object (so)
# Las opciones -fPIC y -shared solo son necesarias para librerias dinamicas
#
CC=gcc
CFLAGS=-Wall -ggdb -fPIC 
LDFLAGS=-fPIC -shared

all: liba.a

#
# LIBRERIA ESTATICA
# Consiste en empaquetar el codigo objeto de los modulos que integran la
# libreria por medio de la utilidad 'ar'Las opciones dadas son
# reemplazar(r), crear(c) y crear un indice del contenido en el propio
# archivo (s).
#
liba.a: a.o a2.o
	ar rcs $@ $^

clean:
	$(RM) *.o *~ *.a


