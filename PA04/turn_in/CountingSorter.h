/**
 * @file
 * @author Matthew Bauer
 * @brief Declaration file for the CountingSorter class.
 */
#ifndef COUNTING_SORTER_H
#define COUNTING_SORTER_H
 
#include "Sorter.h"

/**
 * @brief CountingSorter class.
 */
class CountingSorter : public Sorter
{
public:
	/*
	 * @copybrief Sorter::Sorter()
	 * @details Constructs with name: "Counting Sorter"
	 */
	CountingSorter();

	/**
	 * @copybrief Sorter::sortInPlace(int*, int)
	 * @details Uses the counting sort algorithm.
	 */
	void sortInPlace(int *arr, int len);
};

#endif