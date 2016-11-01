/**
 * @file
 * @author Matthew Bauer
 * @brief Main file for CS302/PA04
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <iostream>
#include <string.h>
#include <fstream>
#include "BubbleSorter.h"
#include "MergeSorter.h"
#include "CountingSorter.h"

// a randsetN is an array of ten pointers to arrays containing N numbers.
int **randset_1k, **randset_10k, **randset_100k;

/**
 * @brief Fills an array with the given number of random integers with values
 *     ranging from 0 to 1000000.
 * @param array The array to fill.
 * @param numInts The number of ints to fill it with.
 * @pre The given array must be allocated with more than numInts*4 bytes of
 *     space.
 * @post The first numInts elements of the array will be filled with random
 *     integers.
 */
 void fillArrayRandomly(int *arr, int numInts)
 {
 	while(numInts--)
 	{
 		*(arr++) = rand()%1000001;
 	}
 }

/**
 * @brief Fill one randset.
 * @param set The randset to fill.
 * @param nval The N-value of the randset.
 * @pre The given randset has not been allocated.
 */
void fillRandset(int**& set, int nval)
{
	set = new int*[10];
	for(int arrIter = 0; arrIter < 10; arrIter++)
	{
		fillArrayRandomly(set[arrIter], nval);
	}
}

/**
 * @brief Fill all randsets appropriately.
 */
void generateRandsets()
{
	srand(time(NULL));
	fillRandset(randset_1k, 1000);
	fillRandset(randset_10k, 10000);
	fillRandset(randset_100k, 100000);
}

/**
 * @brief Free one randset.
 * @param set The randset to free.
 * @pre The randset is allocated and valid.
 * @post The randset pointer will be set to nullptr.
 */
void freeOneRandset(int**& set)
{
	for(int arrIter = 0; arrIter < 10; arrIter++)
	{
		delete set[arrIter];
	}
	delete set;
	set = nullptr;
}

/**
 * @brief Free the memory of all randsets.
 * @post All randset pointers will be set to nullptr.
 */
void freeRandsets()
{
	freeOneRandset(randset_1k);
	freeOneRandset(randset_10k);
	freeOneRandset(randset_100k);
}

/**
 * @brief Test an array on a Sorter.
 * @param sorter The Sorter to test the array on.
 * @param arr The array to test.
 * @param len The length of the array to test.
 * @param sortOut The output stream to print sort results to.
 * @param writeOut Whether output should be added to the stream.
 */
void testArray(Sorter *sorter, int *arr, int len,
	std::stringstream& sortOut, bool writeOut = false)
{
	// copy array
	int *arrCpy = new int[len];
	memcpy(arrCpy, arr, len);

	// sort
	sorter->sortInPlace(arrCpy, len);

	// save results if necessary
	if(writeOut)
	{
		for(int iter = 0; iter < len; iter++)
		{
			sortOut << arrCpy[iter] << std::endl;
		}
		sortOut << "\n\n";
	}

	delete arrCpy;
}

/**
 * @brief Test a randset on a Sorter.
 * @param sorter The Sorter to test the randset on.
 * @param set The randset to test.
 * @param len The length of the arrays in the randset to test.
 * @param sortOut The output stream to print sort results to.
 * @param statOut The output stream to print stats to.
 */
void testRandset(
	Sorter *sorter, int **set, int len,
	std::stringstream& sortOut, std::stringstream& statOut)
{
	statOut << "Testing set with n=" << len << "...\n";
	sortOut << "Testing set with n=" << len << "...\nSample output:\n";
	std::cerr << "\t...with n=" << len << std::endl;

	// only write to sortOut the first time!
	bool writeOut = true;
	for(int arrIter = 0; arrIter < 10; arrIter++)
	{
		std::cerr << "\t\t(" << arrIter+1 << "/10)\n";

		testArray(sorter, set[arrIter], len, sortOut, writeOut);
		writeOut = false;
	}

	// write stats
	SortStats stats = sorter->getStats();
	statOut
		<< "\tAverage CPU Time Used: " << stats.avgCPUTime << "\n"
		<< "\tAverage Number of Comparisons: " << stats.avgNumComparisons << "\n"
		<< "\tAverage Number of Swaps: " << stats.avgNumSwaps << "\n\n";
}

/**
 * @brief Test a Sorter on various data.
 * @param sorter The Sorter to test.
 * @param sortOut The output stream to print sort results to.
 * @param statOut The otuput stream to print stats to.
 * @pre Global randsets have been generated.
 */
void testOneSorter(
	Sorter *sorter,
	std::stringstream& sortOut, std::stringstream& statOut)
{
	// do output niceties
	sortOut
		<< "--------------------\n"
		<< "Testing Sorter: " << sorter->getName() << std::endl;
	statOut
		<< "--------------------\n"
		<< "Testing Sorter: " << sorter->getName() << std::endl;
	std::cerr << "Sorter: " << sorter->getName() << std::endl;

	// 1 call per randset
	testRandset(sorter, randset_1k, 1000, sortOut, statOut);
	testRandset(sorter, randset_10k, 10000, sortOut, statOut);
	testRandset(sorter, randset_100k, 100000, sortOut, statOut);

	// more niceties
	sortOut << "--------------------\n\n";
	statOut << "--------------------\n\n";
}

/**
 * @brief Tests all Sorters fully.
 * @details Prints output to files: sorts.txt, stats.txt
 */
void testSorters(std::stringstream& sortOut, std::stringstream& statOut)
{
	std::cerr << "Testing sorters...\n";

	// initialize sorters
	BubbleSorter bubbler = BubbleSorter();
	MergeSorter merger = MergeSorter();
	CountingSorter counter = CountingSorter();

	// test sorters
	testOneSorter(&bubbler, sortOut, statOut);
	testOneSorter(&merger, sortOut, statOut);
	testOneSorter(&counter, sortOut, statOut);
}

/**
 * @brief Entry point.
 * @return 0 (assumes no failure)
 */
int main()
{
	// generate random numbers
	std::cerr << "Generating randsets...\n";
	generateRandsets();

	// test stuff
	std::stringstream sortOut;
	std::stringstream statOut;
	testSorters(sortOut, statOut);

	// print output
	std::ofstream fhSortOut("sort_results.txt");
	std::ofstream fhStatOut("stats.txt");
	fhSortOut << sortOut.str();
	fhStatOut << statOut.str();

	// clean up
	fhSortOut.close();
	fhStatOut.close();
	freeRandsets();

	return 0;
}