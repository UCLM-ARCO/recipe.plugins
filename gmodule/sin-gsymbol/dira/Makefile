#
# -fPIC indica que se debe generar código independiente de la posicion
# -shared indica que será un objeto compartido -> shared object (so)
# Las opciones -fPIC y -shared solo son necesarias para librerias dinamicas
#
CC=gcc
CFLAGS=-Wall -ggdb -fPIC 
LDFLAGS=-fPIC -shared

all: liba.a liba.so

#
# LIBRERIA ESTATICA
#
# Consiste en empaquetar el codigo objeto de los modulos que integran la libreria 
# por medio de la utilidad 'ar'Las opciones dadas son reemplazar(r), crear(c) y crear
# un indice del contenido en el propio archivo (s).
#
liba.a: a.o a2.o
	ar rcs $@ $^

#
# LIBRERIA DINAMICA
#
# Para dar opciones al montador se utiliza -Wl
# Los flags para el montador se indican separados por comas para que el compilador
# pueda distinguirlos de los que se refieren a él mismo.
#
# -soname es un modificador para el montador y le indica el nombre simbólico
# de la libreria que ha de generar. Este nombre se utiliza para el control de versiones
#
# El compilador necesita un enlace a la libreia cuyo nombre debe ser liba.so. Una vez
# compilado se puede eliminar el enlace.
#
liba.so: a.o a2.o
#	$(CC) -Wl,-soname,liba.so $(LDFLAGS) -o $@ $^
	$(CC) -shared $(LDFLAGS) -o $@ $(filter %.o,$^) $(LDLIBS)

clean:
	$(RM) *.o *~ *.a liba.so


