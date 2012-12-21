CFLAGS = -c -O2
CC = gcc
ARCHIVER = ar
HDLOC=include
OBJS = \
	src/record.o \
	src/scan.o \
	src/select.o \
	src/project.o \
	src/sort.o \

.PHONY: lib		

all: bin/par temp

src/oas_scanner.c src/oas_scanner.h: src/oas_scanner.l
	flex --header-file=src/oas_scanner.h -P oas_ -o src/oas_scanner.c $<

src/oas_parser.c src/oas_parser.h: src/oas_parser.y
	bison -p oas_ -d -o src/oas_parser.c $<

bin/par: src/oas_scanner.c src/oas_scanner.h src/oas_parser.c src/oas_parser.h
	$(CC) $(DEBUG) src/oas_scanner.c src/oas_parser.c -o $@
	make cleanpar

lib: $(OBJS)
	$(ARCHIVER) rcs lib/liboas.a $(OBJS)

src/record.o: src/record.c
	$(CC) $(CFLAGS) $(DEBUG) -I$(HDLOC) $< -o $@

src/select.o: src/select.c
	$(CC) $(CFLAGS) $(DEBUG) -I$(HDLOC) $< -o $@

src/scan.o: src/scan.c
	$(CC) $(CFLAGS) $(DEBUG) -I$(HDLOC) $< -o $@

src/project.o: src/project.c
	$(CC) $(CFLAGS) $(DEBUG) -I$(HDLOC) $< -o $@

src/sort.o: src/sort.c
	$(CC) $(CFLAGS) $(DEBUG) -I$(HDLOC) $< -o $@

debug:
ifneq ($(wildcard lib/liboas.a),)
	rm lib/liboas.a
endif
	$(eval DEB := -Wall -g -ggdb)
	$(CC) $(CFLAGS) $(DEB) -I$(HDLOC) src/record.c -o src/record.o
	$(CC) $(CFLAGS) $(DEB) -I$(HDLOC) src/select.c -o src/select.o
	$(CC) $(CFLAGS) $(DEB) -I$(HDLOC) src/scan.c -o src/scan.o
	$(CC) $(CFLAGS) $(DEB) -I$(HDLOC) src/project.c -o src/project.o
	$(CC) $(CFLAGS) $(DEB) -I$(HDLOC) src/sort.c -o src/sort.o
	$(ARCHIVER) rcs lib/liboas.a $(OBJS)

temp: $(OBJS) shells/temp.o
	$(CC) $(DEBUG) -I$(HDLOC) $(OBJS) shells/temp.o -o shells/$@

shells/temp.o: shells/temp.c
	$(CC) $(CFLAGS) -I$(HDLOC) $(DEBUG) $< -o $@

cleanpar:
	rm src/oas_scanner.c src/oas_scanner.h src/oas_parser.c src/oas_parser.h

cleantemp:
	rm -rf bin/temp*

cleanobjs:
	rm src/*o

cleanall: cleanpar cleantemp cleanobjs
