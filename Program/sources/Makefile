#Nicolas CAILLOUX (Lasconik)
PROGRAM=MyBadPunchOut
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
LIBREP=$(HOME)/.SFML2
CC=g++ -std=c++0x
CPPFLAGS=
CFLAGS=-Wall -g
IFLAGS= -I$(LIBREP)/include
LDFLAGS=-L$(LIBREP)/lib -lsfml-graphics -lsfml-window -lsfml-system

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

%.o:%.cpp
	@echo "building "$@;
	$(CC) $(CFLAGS) -c $< $(IFLAGS)

%.d:%.cpp
	@echo "building "$@;
	$(CC) $(CFLAGS) -MM $< $(IFLAGS)

clean:
	@echo "building "$@;
	rm -f $(PROGRAM) $(OBJECTS) *.d *~
