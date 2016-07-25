# Makefile for Sierpinski
#****************************************************************

PROGRAM = Sierpinski
OBJECTS = Sierpinski.o

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden -g
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

Sierpinski: $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

Sierpinski.o: Sierpinski.cpp Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) Sierpinski.cpp

libStanfordCPPLib.a:
	@rm -f libStanfordCPPLib.a
	(cd StanfordCPPLib; make all)
	ln -s StanfordCPPLib/libStanfordCPPLib.a .


# ***************************************************************
# Standard entries to remove files from the directories
#    tidy  -- eliminate unwanted files
#    clean -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out *.err

clean scratch: tidy
	rm -f *.o *.a $(PROGRAM)
