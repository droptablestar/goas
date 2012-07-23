CFLAGS = -c
CC = gcc
ARCHIVER = ar
LIBLOC = lib/
LIBNAME = -loas
OBJS = \
	src/record.o \
	src/scan.o \
	src/select.o \
	src/project.o \
	src/sort.o \

all: src/par src/temp

src/oas_scanner.c src/oas_scanner.h: src/oas_scanner.l
	flex --header-file=src/oas_scanner.h -P oas_ -o src/oas_scanner.c $<

src/oas_parser.c src/oas_parser.h: src/oas_parser.y
	bison -p oas_ -d -o src/oas_parser.c $<

bin/par: src/oas_scanner.c src/oas_scanner.h src/oas_parser.c src/oas_parser.h
	$(CC) $(DEBUG) src/oas_scanner.c src/oas_parser.c -o $@
	make cleanpar

bin/temp: src/temp.c
	$(CC) $< -L$(LIBLOC) $(LIBNAME) -o $@

lib/liboas: $(OBJS)
	$(ARCHIVER) rcs lib/liboas.a $(OBJS)
	make cleanobjs

bin/tempD: $(OBJS) src/temp.o
	$(CC) $(DEBUG) $(OBJS) src/temp.o -o $@

src/record.o: src/record.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

src/select.o: src/select.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

src/scan.o: src/scan.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

src/project.o: src/project.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

src/sort.o: src/sort.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

src/temp.o: src/temp.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

cleanpar:
	rm src/oas_scanner.c src/oas_scanner.h src/oas_parser.c src/oas_parser.h

cleantemp:
	rm -rf src/temp*

cleanobjs:
	rm src/*o

cleanbin:
	rm -rf bin/*

cleanall: cleanpar cleantemp cleanobjs
