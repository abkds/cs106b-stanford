# Makefile for Priority Queue
#****************************************************************

PROGRAM = PriorityQueue
OBJECTS = pqueue-test.o pqueue-vector.o pqueue-linkedlist.o pqueue-doublylinkedlist.o pqueue-heap.o pqueue-extra.o
HEADERS = pqueue-vector.h pqueue-linkedlist.h pqueue-doublylinkedlist.h pqueue-heap.h pqueue-extra.h

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden -g
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

PriorityQueue: $(OBJECTS) $(HEADERS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

pqueue-test.o: pqueue-test.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) pqueue-test.cpp

pqueue-vector.o: pqueue-vector.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) pqueue-vector.cpp

pqueue-linkedlist.o: pqueue-linkedlist.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) pqueue-linkedlist.cpp

pqueue-doublylinkedlist.o: pqueue-doublylinkedlist.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) pqueue-doublylinkedlist.cpp

pqueue-heap.o: pqueue-heap.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) pqueue-heap.cpp

pqueue-extra.o: pqueue-extra.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) pqueue-extra.cpp

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
