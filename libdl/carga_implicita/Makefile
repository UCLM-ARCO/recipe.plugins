#
# Este fichero genera un programa main que hace uso de una libreria dinamica (liba.so)
# y de un plugin, es decir, una libreria enlazada en tiempo de ejecución (libb.so).
#
# Observando los flags al compilador vemos que no hay referencias a libb
# El flag -ldl se refiere a la libreria libdl.so que permite hacer enlaces dinamicos
# 
CC=gcc
CFLAGS=-Wall -ggdb -Idira -fPIC
LDFLAGS=-Ldira  -rdynamic
LDLIBS=-la -ldl

all: libs main

main: main.o 
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

