/**
 * @file
 * @author Matthew Bauer
 * @brief Declaration file for the MergeSorter class.
 */
#ifndef MERGE_SORTER_H
#define MERGE_SORTER_H

#include "Sorter.h"

/**
 * @brief MergeSorter class.
 */
class MergeSorter : public Sorter
{
private:
	/**
	 * @brief Merge two arrays in the right way.
	 * @param part1 The first part to merge.
	 * @param len1 The length of the first part.
	 * @param part2 The second part to merge.
	 * @param len2 The length of the second part.
	 * @param dest The merge destination.
	 * @pre The length of dest >= len1+len2
	 */
	void mergeParts(
		int *part1, int len1,
		int *part2, int len2,
		int *dest);

	/**
	 * @brief The recursive layer for merge sort.
	 * @param arr The array to sort.
	 * @param len The length of the array to sort
	 */
	void sortRecursive(int *arr, int len);

public:
	/**
	 * @copybrief Sorter::Sorter()
	 * @details Constructs with name: "Merge Sorter"
	 */
	MergeSorter();

	/**
	 * @copybrief Sorter::sortInPlace(int*, int)
	 * @details Uses the merge sort algorithm.
	 */
	void sortInPlace(int *arr, int len);
};

#endif