PROGRAM=LordzOfTheRing
LIB=src/lib64

all:sub

sub:
	cd src;	make
	cp src/$(PROGRAM) $(PROGRAM)

clean:
	cd src;	make clean;

proper:clean
	cd src; make proper;

valgrind:
	export LD_LIBRARY_PATH=$(LIB) && valgrind ./$(PROGRAM)

start:
	export LD_LIBRARY_PATH=$(LIB) && ./$(PROGRAM) ../resources/
