CFLAGS = -c -O2
OMP = -fopenmp
CC = gcc
ARCHIVER = ar
LIBLOC = lib/
HDLOC = -Iinclude
LIBNAME = -loas -O2
OBJS = \
	src/record.o \
	src/scan.o \
	src/select.o \
	src/project.o \
	src/sort.o \

all: src/par temp

src/oas_scanner.c src/oas_scanner.h: src/oas_scanner.l
	flex --header-file=src/oas_scanner.h -P oas_ -o src/oas_scanner.c $<

src/oas_parser.c src/oas_parser.h: src/oas_parser.y
	bison -p oas_ -d -o src/oas_parser.c $<

bin/par: src/oas_scanner.c src/oas_scanner.h src/oas_parser.c src/oas_parser.h
	$(CC) $(DEBUG) src/oas_scanner.c src/oas_parser.c -o $@
	make cleanpar

lib/liboas: $(OBJS)
	$(ARCHIVER) rcs lib/liboas.a $(OBJS)
	make cleanobjs

temp: temp.c
	$(CC) $(OMP) $(HDLOC) -L$(LIBLOC) $(LIBNAME) $< -o $@

tempD: $(OBJS) temp.o
	$(CC) $(OMP) $(HDLOC) $(DEBUG) $(OBJS) temp.o -o $@

src/record.o: src/record.c
	$(CC) $(CFLAGS) $(OMP) $(HDLOC) $(HDLOC) $(DEBUG) $< -o $@

src/select.o: src/select.c
	$(CC) $(CFLAGS) $(OMP) $(HDLOC) $(DEBUG) $< -o $@

src/scan.o: src/scan.c 
	$(CC) $(CFLAGS) $(HDLOC) $(DEBUG) $< -o $@

src/project.o: src/project.c 
	$(CC) $(CFLAGS) $(OMP) $(HDLOC) $(DEBUG) $< -o $@

src/sort.o: src/sort.c 
	$(CC) $(CFLAGS) $(HDLOC) $(DEBUG) $< -o $@

temp.o: temp.c
	$(CC) $(CFLAGS) $(HDLOC) $(DEBUG) $< -o $@

cleanpar:
	-rm src/oas_scanner.c src/oas_scanner.h src/oas_parser.c src/oas_parser.h

cleantemp:
	-rm temp* bin/temp

cleanobjs:
	-rm src/*o

cleanall: cleantemp cleanobjs cleanpar
	-rm -rf bin/*
