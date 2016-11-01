/**
 * @file
 * @author Matthew Bauer
 * @brief Implementation file for the BubbleSorter class.
 */
#include "BubbleSorter.h"
#include <utility>
#include <ctime>
#include <chrono>

// BubbleSorter defs
BubbleSorter::BubbleSorter()
{
	name = "Bubble Sorter";
	resetStats();
}

void BubbleSorter::sortInPlace(int *arr, int len)
{
	bool oneSwapped = false; // if a swap happened in this pass

	startTimer();
	do
	{
		oneSwapped = false;
		for(int toSwap = 0; toSwap < len-1; toSwap++)
		{ // toSwap = the FIRST element in the swap pair
			totNumComparisons++;
			if(arr[toSwap] > arr[toSwap+1])
			{
				oneSwapped = true;
				std::swap(arr[toSwap], arr[toSwap+1]);
				totNumSwaps++;
			}
		}
	}
	while(oneSwapped);
	stopTimer();
	
    sortsRun++;
}
