.phony: all clean
.phony: debug clean

CC = gcc
CFLAGS = -c
PT = -pthread
OBJS = \
	record.o \
	scan.o \
	select.o \
	project.o \
	sort.o \
	main.o

all: exe

exe: $(OBJS)
	$(CC) $(DEBUG) $(OBJS) -o $@
	-rm -rf /cores/*

record.o: record.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

select.o: select.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

scan.o: scan.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

project.o: project.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

sort.o: sort.c 
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

clean:
	rm -rf *o exe exe.dSYM