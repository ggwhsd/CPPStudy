CCFLAGS = ${CFLAG}
cc = g++
buildFolder=lib/
prom = $(buildFolder)libhello.so
srcFolder=gen/

deps = $(srcFolder)hello.h
src = $(srcFolder)hello.cpp
obj = $(buildFolder)hello.o

header_path = 
CCFLAGS += -Wall
LIBSO = -shared -fPIC

show:
	@echo "show how to use two steps to compile and link objects to so.  you can also use one step to do these things. Here's just a demo example."

link:compile
	@echo "link" $(obj)  $(prom)
	$(cc) $(LIBSO) -o  $(prom) $(obj)

compile:
	@echo "compile" $(src)  $(obj)
	$(cc) ${CCFLAGS} -c $(src) -o $(obj) $(header_path)

target:link show
	@echo "compile target exec" "test.cpp" "test.out"
	$(cc) ${CCFLAGS} test.cpp -o test.out -L./lib -lhello



	

.PHONY: clean compile link target
clean:
	rm -rf $(obj) $(prom)
