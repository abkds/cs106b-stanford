/*
 * File: InverseGenetics.cpp
 * ----------------------
 * This file is the starter project for the InverseGenetics problem
 * on Assignment #3.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>

/* Function: listAllRNAStrandsFor(string protein,
 *                                std::map<char, std::set<std::string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
std::set<std::string> listAllRNAStrandsFor(std::string protein,
	std::map<char, std::set<std::string> >& codons);

/* Function: loadCodonMap();
 * Usage: std::map<char, std::set<string> > codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
std::map<char, std::set<std::string> > loadCodonMap();
static int x = 0;

int main() {
	/* Load the codon map. */
	std::map<char, std::set<std::string> > codons = loadCodonMap();

	std::cout << "Enter the input protein: ";
	std::string inputProtein;
	getline(std::cin, inputProtein);

	std::set<std::string> rnaStrands =
		listAllRNAStrandsFor(inputProtein, codons);

	for (auto it = rnaStrands.begin(); it != rnaStrands.end(); ++it) {
		std::cout << *it << std::endl;
	}
	return 0;
}



/*
 * Implementation notes
 * --------------------
 * Uses the recursive strategy, to find the rna strands for all the protein
 * except the first protein. Then it recursively adds all the rna, remaining
 * strands for the current protein, forms a set.
 * Base case is when there is only a single protein, in which case the list
 * of all the rna for that single protein are returned.
 */
std::set<std::string> listAllRNAStrandsFor(std::string protein,
	std::map<char, std::set<std::string> >& codons) {

	std::set<std::string> rnaStrands;
	/*
	 * Base case if protein is zero length,
	 * there are no RNA strands
	 */
	if (protein.size() == 1) {
		for (auto it = codons[protein[0]].begin();
			it != codons[protein[0]].end();
			++it) {
			rnaStrands.insert(*it);
		}
		return rnaStrands;
	}

	std::set<std::string> rnaStrandsRemaining =
		listAllRNAStrandsFor(protein.substr(1), codons);

	for (auto it = codons[protein[0]].begin();
		it != codons[protein[0]].end();
		++it) {

		for (auto it_ = rnaStrandsRemaining.begin();
			it_ != rnaStrandsRemaining.end();
			++it_) {
			rnaStrands.insert((*it) + (*it_));
		}
	}

	return rnaStrands;
}

/* You do not need to change this function. */
std::map<char, std::set<std::string> > loadCodonMap() {
	std::ifstream input("codons.txt");
	std::map<char, std::set<std::string> > result;

	/* The current codon / protein combination. */
	std::string codon;
	char protein;

	/* Continuously pull data from the file until all data has been
	 * read.
	 */
	while (input >> codon >> protein) {
		result[protein].insert(codon);
	}

	return result;
}
