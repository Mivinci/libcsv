prefix=/usr/local
incdir=$(prefix)/include
libdir=$(prefix)/lib

LIB=libcsv.a

all:
	gcc -o $(LIB) -c csv.c

.PHONY: install uninstall

install:
	cp -v $(LIB) $(libdir)
	cp -v csv.h $(incdir)

uninstall:
	rm $(libdir)/$(LIB)
	rm $(incdir)/csv.h

