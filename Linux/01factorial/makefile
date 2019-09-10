G = g++
C = gcc
CFLAGS = -Wall -O -g
TARGET = factorial 

OBJS = main.o factorial.o
SOURCES = main.c factorial.c 

all:$(TARGET) bug hello

$(TARGET): $(OBJS)
	$(G) $(OBJS) -o $(TARGET)
	@chmod a+x $(TARGET)

main.o: main.c
	$(G) $(CFLAGS) -c main.c

factorial.o: factorial.c
	$(G) $(CFLAGS) -c factorial.c

bug:bug.o
	$(G) $< -o $@

bug.o:bug.c
	$(G) $(CFLAGS) -c $<

hello:hello.o
	$(G) $< -o $@
	
hello.o:hello.C
	$(G) $(CFLAGS) -c $<
	
clean:
	rm -rf *.o factorial bug

show:
	@echo $(OBJS)
