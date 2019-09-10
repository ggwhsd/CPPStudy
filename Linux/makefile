dirs = 01factorial

all:
	@for dir in $(dirs); do \
		make -C $$dir all -f makefile; \
	done
clean:
	@for dir in $(dirs); do \
		make -C $$dir clean -f makefile; \
	done
.PHONY: all clean
