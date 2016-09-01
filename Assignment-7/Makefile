# Makefile for Trailblazer
#****************************************************************

PROGRAM = Trailblazer
OBJECTS = Trailblazer.o WorldGenerator.o TrailblazerGraphics.o TrailblazerTypes.cpp TrailblazerCosts.o
HEADERS = TrailblazerPQueue.h WorldGenerator.h Trailblazer.h TrailblazerGraphics.h TrailblazerTypes.h TrailblazerCosts.h TrailblazerConstants.h

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden -g
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

Trailblazer: $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

Trailblazer.o: Trailblazer.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) Trailblazer.cpp

TrailblazerGraphics.o: TrailblazerGraphics.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) TrailblazerGraphics.cpp

WorldGenerator.o: WorldGenerator.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) WorldGenerator.cpp

TrailblazerTypes.o: TrailblazerTypes.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) TrailblazerTypes.cpp
	
TrailblazerCosts.o: TrailblazerCosts.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) TrailblazerCosts.cpp	

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
