/**
 * @file
 * @author Matthew Bauer
 * @brief Implementation file for the MergeSorter class.
 */
#include "MergeSorter.h"
#include <ctime>
#include <string.h>

// MergeSorter defs
MergeSorter::MergeSorter()
{
	name = "Merge Sorter";
	resetStats();
}

void MergeSorter::mergeParts(
	int *part1, int len1,
	int *part2, int len2,
	int *dest)
{
	while(len1 && len2)
	{
		if(*part1 < *part2)
		{
			*dest = *part1;
			// move forward in part1
			part1++;
			len1--;
		}
		else
		{
			*dest = *part2;
			// move forward in part2
			part2++;
			len2--;
		}
		dest++; // move forward in dest

		// update stat counters
		totNumComparisons++;
		totNumSwaps++;
	}

	// place whatever's left over
	if(len1)
	{
		memcpy(dest, part1, len1);
		totNumSwaps += len1;
	}
	else
	{
		memcpy(dest, part2, len2);
		totNumSwaps += len2;
	}
}

void MergeSorter::sortRecursive(int *arr, int len)
{
	if(len == 1)
	{ // base case
		return arr;
	}
	int *arrCpy = new int[len];
	memcpy(arrCpy, arr, len);

	// len/2 --> floor(len/2) b/c int arithmetic
	sortRecursive(arrCpy, len/2);
	sortRecursive(arrCpy+(len/2), len-(len/2));

	mergeParts(
		arrCpy, len/2,
		arrCpy+(len/2), (len/2)+1,
		arr);
}

void MergeSorter::sortInPlace(int *arr, int len)
{
	long startCPU = (long)clock();
	sortRecursive(arr, len);
	totCPUTime += (int)(clock() - startCPU);
}