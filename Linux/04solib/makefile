CC = g++
CFLAGS_DEBUG = -std=c++11 -Wall -O0 -g3 -c
CFLAGS_RELEASE = -std=c++11 -Wall -O2 -c
INCS = .
TARGET = libhello.so
OBJS = libhello.o

all:$(TARGET) usehello_so post_build

$(TARGET):$(OBJS)
	@echo "Linking..."
	g++ -shared -fPIC -o $@ $<
	@echo "Building Sucess ---> $@"	

libhello.o:libhello.c libhello.h
	g++ -c -fPIC libhello.c

usehello_so:libhello.so usehello.o
	g++ usehello.o -L./ -lhello  -o $@

usehello.o:usehello.c
	g++ -c  usehello.c

post_build:usehello_so
	echo "export $LD_LIBRARY_PATH=`pwd`">Start.sh
	echo "./usehello_so" >>Start.sh
	chmod u+x Start.sh

clean:
	rm *.o *.so usehello_so

