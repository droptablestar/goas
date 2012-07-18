CFLAGS = -c \
	-I oasfrontend
CC = gcc
OBJS = \
	oasfrontend/record.o \
	oasfrontend/scan.o \
	oasfrontend/select.o \
	oasfrontend/project.o \
	oasfrontend/sort.o \
	temp.o

all: par temp
oas_scanner.c oas_scanner.h: oas_scanner.l
	flex --header-file=oas_scanner.h -P oas_ -o oas_scanner.c $<

oas_parser.c oas_parser.h: oas_parser.y
	bison -p oas_ -d -o oas_parser.c $<

par: oas_scanner.c oas_scanner.h oas_parser.c oas_parser.h
	$(CC) $(DEBUG) oas_scanner.c oas_parser.c -o par

temp: $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o $@

oasfrontend/record.o: oasfrontend/record.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

oasfrontend/select.o: oasfrontend/select.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

oasfrontend/scan.o: oasfrontend/scan.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

oasfrontend/project.o: oasfrontend/project.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

oasfrontend/sort.o: oasfrontend/sort.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

temp.o: temp.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

clean:
	rm -rf temp* oas_scanner.c oas_scanner.h oas_parser.c oas_parser.h par*

cleanall: clean 
	rm -rf oasfrontend/*o
