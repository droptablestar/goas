CFLAGS = -c \
	-I lib
CC = gcc
OBJS = \
	lib/record.o \
	lib/scan.o \
	lib/select.o \
	lib/project.o \
	lib/sort.o \
	temp.o

all: par temp
lib/oas_scanner.c lib/oas_scanner.h: lib/oas_scanner.l
	flex --header-file=lib/oas_scanner.h -P oas_ -o lib/oas_scanner.c $<

lib/oas_parser.c lib/oas_parser.h: lib/oas_parser.y
	bison -p oas_ -d -o lib/oas_parser.c $<

par: lib/oas_scanner.c lib/oas_scanner.h lib/oas_parser.c lib/oas_parser.h
	$(CC) $(DEBUG) lib/oas_scanner.c lib/oas_parser.c -o lib/par

temp: $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o $@

lib/record.o: lib/record.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

lib/select.o: lib/select.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

lib/scan.o: lib/scan.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

lib/project.o: lib/project.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

lib/sort.o: lib/sort.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

temp.o: temp.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

clean:
	rm -rf temp* lib/oas_scanner.c lib/oas_scanner.h lib/oas_parser.c \
  lib/oas_parser.h lib/par*

cleanall: clean 
	rm -rf lib/*o
