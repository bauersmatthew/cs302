/**
 * @file
 * @author Matthew Bauer
 * @brief Delcaration file for the BubbleSorter class.
 */
#ifndef BUBBLE_SORTER_H
#define BUBBLE_SORTER_H

#include "Sorter.h"

/**
 * @brief BubbleSorter class.
 */
class BubbleSorter : public Sorter
{
public:
	/**
	 * @copybrief Sorter::Sorter()
	 * @details Constructs with name: "Bubble Sorter"
	 */
	BubbleSorter();

	/**
	 * @copybrief Sorter::sortInPlace(int*, int)
	 * @details Uses the bubble sort algorithm.
	 */
	void sortInPlace(int *arr, int len);
};

#endif