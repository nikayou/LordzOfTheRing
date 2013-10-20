#Nicolas CAILLOUX (Lasconik)
PROGRAM=LordzOfTheRing
SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXX=g++
CXXFLAGS := -std=c++0x -Wall -Wextra -pedantic-errors
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: $(PROGRAM)

show:
	@echo "ld : "$(LDFLAGS);
	@echo "sources : "$(SOURCES);
	@echo "objects : "$(OBJECTS);
	@echo "command : "$(CXX) $(CXXFLAGS);

$(PROGRAM):$(OBJECTS)
	@echo "building "$@;
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	cp $(PROGRAM) ../$(PROGRAM)

%.o:%.d
	$(CXX) -c $(CXXFLAGS) $<

%.d:%.cpp
	$(CXX) -M $(CXXFLAGS) $<

clean:
	rm -f $(PROGRAM) $(OBJECTS) *.d *~

