
all: test liba.so libb.so libd.so

test: LDLIBS=-ldl -ld `pkg-config --libs gmodule-2.0` `pkg-config --libs glib-2.0`
test: LDFLAGS=-L. --export-dynamic
test: CFLAGS=-fPIC -ggdb -Wall `pkg-config --cflags glib-2.0` `pkg-config --cflags gmodule-2.0`
test: test.o libd.so

liba.so: LDFLAGS=
liba.so: LDLIBS=
liba.so: CFLAGS=-Wall -fPIC
liba.so: a.o

libb.so: CFLAGS=-ggdb -Wall -fPIC
libb.so: LDFLAGS=-L.
libb.so: LDLIBS=-la
libb.so: b.o liba.so

libd.so: LDFLAGS=-L.
libd.so: LDLIBS=
libd.so: CFLAGS=-ggdb -Wall -fPIC
libd.so: c.o

%.so:
	$(CC) -shared $(LDFLAGS) -o $@ $(filter %.o,$^) $(LDLIBS)

clean:
	$(RM) *.o *~ lib*.so test
