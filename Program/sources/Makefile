#Nicolas CAILLOUX (Lasconik)
PROGRAM=LordzOfTheRing
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CC=g++ -std=c++11
CPPFLAGS=
CFLAGS=-Wall -g
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: clean show $(PROGRAM)

show:
	@echo "librep : "$(LIBREP);
	@echo "include : "$(IFLAGS);
	@echo "ld : "$(LDFLAGS);
	@echo "sources : "$(SOURCES);
	@echo "objects : "$(OBJECTS);

$(PROGRAM):$(OBJECTS)
	@echo "building "$@;
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	cp $(PROGRAM) ../$(PROGRAM)

%.o:%.d
	@echo "building "$@;
	$(CC) $(CFLAGS) -c $< $(IFLAGS)

%.d:%.cpp
	@echo "building "$@;
	$(CC) $(CFLAGS) -MM $< $(IFLAGS)

clean:
	@echo "building "$@;
	rm -f $(PROGRAM) $(OBJECTS) *.d *~

