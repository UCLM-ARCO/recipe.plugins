#
# Este fichero genera un programa main que hace uso de una libreria dinamica (liba.so)
# y de un plugin, es decir, una libreria enlazada en tiempo de ejecución (libb.so).
#
# Observando los flags al compilador vemos que no hay referencias a libb
# El flag -ldl se refiere a la libreria libdl.so que permite hacer enlaces dinamicos
# 
CC=gcc
CFLAGS=-Wall -ggdb -Idira -fPIC
LDFLAGS=-Ldira -L. --export-dynamic
LDLIBS=-la -ldl 

all: libs main

main: main.o libd.so

libd.so: LDFLAGS=-L.
libd.so: LDLIBS=
libd.so: CFLAGS=-ggdb -Wall -fPIC
libd.so: c.o

%.so:
	$(CC) -shared $(LDFLAGS) -o $@ $(filter %.o,$^) $(LDLIBS)

#
# Estas reglas ejecutan los makefiles que hay en los subdirectorios
#
libs:
	$(MAKE) -C dira
	$(MAKE) -C dirb

clean:
	$(RM) *.o *~ main *.so
	$(MAKE) -C dira clean
	$(MAKE) -C dirb clean

