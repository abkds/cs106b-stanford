/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"
#include "pqueue.h"
#include <vector>
#include <string>
#include <utility>
using namespace std;

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
Map<ext_char, int> getFrequencyTable(istream& file) {
	Map<ext_char, int> frequencyTable;
	frequencyTable[PSEUDO_EOF] = 1;

	char c;
	while (file.get(c)) {
		frequencyTable[c]++;
	}

	return frequencyTable;
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	/* Priority queue to hold nodes of Huffman encoding tree */
	PriorityQueue<Node*> nodesPQ;

	foreach (ext_char character in frequencies) {
		Node * node = new Node;
		node->character = character;
		node->one = NULL;
		node->zero = NULL;
		node->weight = frequencies[character];

		nodesPQ.enqueue(node, node->weight);
	}

	while (!nodesPQ.isEmpty()) {
		Node * node1 = nodesPQ.dequeue();
		if (nodesPQ.isEmpty()) return node1;

		/* More than one node combine them */
		Node * node2 = nodesPQ.dequeue();
		Node * parent = new Node;
		parent->zero = node1;
		parent->one = node2;
		parent->character = NOT_A_CHAR;
		parent->weight = node1->weight + node2->weight;

		nodesPQ.enqueue(parent, parent->weight);
	}

	return NULL;
}

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	if (root == NULL) return;

	freeTree(root->one);
	freeTree(root->zero);
	delete root;

}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	Map<ext_char, string> map = getEncodedPatternMap(encodingTree);

	char character;
	while (infile.get(character)) {
		writeBitPattern(outfile, map[character]);
	}

	writeBitPattern(outfile, map[PSEUDO_EOF]);
}

/* Function: getEncodedPatternMap
 * Usage: map = getEncodedPatternMap(tree)
 * ---------------------------------------
 * Generates a map of pattern strings for all the characters stored
 * as leaves in the encoded tree.
 */
Map<ext_char, string> getEncodedPatternMap(Node * root) {
	Map<ext_char, string> map;

	vector<pair<ext_char, string> > pairs = encodedPatterns(root);

	for (int i = 0; i < pairs.size(); i++) {
		map[pairs[i].first] = pairs[i].second;
	}

	return map;
}

/* Function: encodingPattern
 * Usage: pattern = encodingPattern(character, tree)
 * -------------------------------------------------
 * Returns the encoded bit pattern for a given bit pattern
 * stored in the tree.
 */
vector<pair<ext_char, string> > encodedPatterns(Node * encodingTree) {
	string pattern;
	vector<pair<ext_char, string> > pairs;
	encodedPatternUtility(encodingTree, pairs, pattern);
	return pairs;
}

/* Function: encodedPatternUtility
 * Usage: encodedPatternUtility(tree, pairs, pattern)
 * --------------------------------------------------
 * Utility function to find all the character pattern pairs,
 * once it reaches any leaf, recursion stops and stores the pair
 * in the pairs.
 */
void encodedPatternUtility(Node * tree, vector<pair<ext_char, string> >& pairs,
	string pattern) {

	if (tree == NULL) return;
	if (tree->one == NULL && tree->zero == NULL) {
		pairs.push_back(make_pair(tree->character, pattern));
	}

	encodedPatternUtility(tree->one, pairs, pattern + "1" );
	encodedPatternUtility(tree->zero, pairs, pattern + "0");
}

/* Function: writeBitPattern
 * Usage: writeBitPattern(outfile, pattern)
 * ----------------------------------------
 * Writes to output bit stream the bits as stored in the pattern
 * Takes as input a string containing "0" and "1". No error checking
 * is applied on the string characters provided.
 */
void writeBitPattern(obstream& outfile, const string& pattern) {
	int bit;
	for (int i = 0; i < pattern.size(); i++) {
		bit = pattern[i] == '1' ? 1 : 0;
		outfile.writeBit(bit);
	}
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	Map<ext_char, string> encodedMap = getEncodedPatternMap(encodingTree);
	Map<string, ext_char> decodeMap;

	/* Inverse mapping of map to decode */
	foreach (ext_char ch in encodedMap) {
		decodeMap[encodedMap[ch]] = ch;
	}

	string pattern;
	int bit;
	int i = 0;
	while (true) {
		bit = infile.readBit();
		(bit == 1) ? pattern += "1" : pattern += "0";

		if (decodeMap.containsKey(pattern)) {
			ext_char ch = decodeMap[pattern];
			if (ch == PSEUDO_EOF) return;
			char ch_ = (char) ch;
			file.put(ch_);
			pattern = "";
		}
	}
}

/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */

	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}

	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';

	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;

		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;

	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;

	/* Skip trailing whitespace. */
	infile.get();

	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();

		/* Get the frequency. */
		int frequency;
		infile >> frequency;

		/* Skip the space character. */
		infile.get();

		/* Add this to the encoding table. */
		result[ch] = frequency;
	}

	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
	Map<ext_char, int> frequencies = getFrequencyTable(infile);
	infile.rewind();
	writeFileHeader(outfile, frequencies);
	Node* encodingTree = buildEncodingTree(frequencies);
	encodeFile(infile, encodingTree, outfile);
	freeTree(encodingTree);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
	Map<ext_char, int> frequencies = readFileHeader(infile);
	Node* encodingTree = buildEncodingTree(frequencies);
	decodeFile(infile, encodingTree, outfile);
	freeTree(encodingTree);
}
