# Makefile for Boggle
#****************************************************************

PROGRAM = Boggle
OBJECTS = Boggle.o gboggle.o BoggleGame.o

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden -g
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

Boggle: $(OBJECTS)
	g++ -std=c++11 -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

Boggle.o: Boggle.cpp Makefile libStanfordCPPLib.a
	g++ -std=c++11 -c $(CPPOPTIONS) Boggle.cpp

gboggle.o: gboggle.cpp Makefile libStanfordCPPLib.a
	g++ -std=c++11 -c $(CPPOPTIONS) gboggle.cpp

BoggleGame.o: BoggleGame.cpp Makefile libStanfordCPPLib.a
    g++ -std=c++11 -c $(CPPOPTIONS) Boggle.cpp

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
