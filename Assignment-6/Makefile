# Makefile for Huffman Encoding
#****************************************************************

PROGRAM = Huffman
BUILDOBJECTS = HuffmanEncoding.o bstream.o HuffmanEncodingTest.o MemoryDiagnostics.o
OBJECTS = ReferenceHuffmanEncoding.o $(BUILDOBJECTS)
HEADERS = bstream.h HuffmanEncoding.h HuffmanTypes.h MemoryDiagnostics.h ReferenceHuffmanEncoding.h

CPPOPTIONS = -IStanfordCPPLib -fvisibility-inlines-hidden -g -funsigned-char
LDOPTIONS = -L.
LIB = -lStanfordCPPLib

# ***************************************************************
# Entry to bring the package up to date
#    The "make all" entry should be the first real entry

all: $(PROGRAM)

Huffman: $(OBJECTS)
	g++ -o $(PROGRAM) $(LDOPTIONS) $(OBJECTS) $(LIB)

HuffmanEncoding.o: HuffmanEncoding.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) HuffmanEncoding.cpp

HuffmanEncodingTest.o: HuffmanEncodingTest.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) HuffmanEncodingTest.cpp

MemoryDiagnostics.o: MemoryDiagnostics.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) MemoryDiagnostics.cpp

bstream.o: bstream.cpp $(HEADERS) Makefile libStanfordCPPLib.a
	g++ -c $(CPPOPTIONS) bstream.cpp

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
	rm -f $(BUILDOBJECTS) *.a $(PROGRAM)
