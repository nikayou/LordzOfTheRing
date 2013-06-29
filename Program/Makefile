#Nicolas CAILLOUX (Lasconik)
PROGRAM=MyBadPunchOut
SRCDIR=sources

all: MyBadPunchOut

MyBadPunchOut:
	cd $(SRCDIR); make
	cd ../
	mv ./$(SRCDIR)/$(PROGRAM) $(PROGRAM)

clean : 
	rm *~
	rm $(PROGRAM)
	cd $(SRCDIR); make clean
