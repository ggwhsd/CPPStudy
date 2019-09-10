CC = g++
CFLAGS_DEBUG = -std=c++11 -Wall -O0 -g3 -c
CFLAGS_RELEASE = -std=c++11 -Wall -O2 -c
INCS = .
TARGET = libhello.a
OBJS = libhello.o

all:$(TARGET) usehello_static

$(TARGET):$(OBJS)
	@echo "Linking..."
	ar -rc $@ $<
	@echo "Building Sucess ---> $@"	

libhello.o:libhello.c libhello.h
	g++ -c  libhello.c

usehello_static:libhello.a usehello.o
	g++ usehello.o -L./ -lhello  -o $@

usehello.o:usehello.c
	g++ -c usehello.c

clean:
	rm *.o *.a usehello_static

