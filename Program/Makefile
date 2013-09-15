#Nicolas CAILLOUX (Lasconik)
PROGRAM=LordzOfTheRing
SRCDIR=sources

all: $(PROGRAM)

$(PROGRAM):
	cd $(SRCDIR); make
	cd ../
	mv ./$(SRCDIR)/$(PROGRAM) $(PROGRAM)

clean : 
	rm *~
	rm $(PROGRAM)
	cd $(SRCDIR); make clean
