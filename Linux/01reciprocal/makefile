G = g++
C = gcc
CFLAGS = -std=c++11 -Wall -O -g
TARGET = reciprocal 


SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))

all:$(TARGET)


%.o:%.c
	$(G) $(CFLAGS) -c $<

%.o:%.cpp
	$(G) $(CFLAGS) -c $<

$(TARGET): $(OBJS)
	$(G) $(OBJS) -o $(TARGET)
	@chmod a+x $(TARGET)

clean:
	ls -l
	rm -rf *.o $(TARGET)
	ls -l

show:
	@echo $(OBJS)
