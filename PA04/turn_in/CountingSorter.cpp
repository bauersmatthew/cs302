/**
 * @file
 * @author Matthew Bauer
 * @brief Implementation file for the CountingSorter class.
 */
#include "CountingSorter.h"
#include <ctime>
#include <string.h>

// CountingSorter defs
CountingSorter::CountingSorter()
{
	name = "Counting Sorter";
	resetStats();
}

void CountingSorter::sortInPlace(int *arr, int len)
{
    int *counts = new int[1000001]; // for counting occurances
	memset((int*)counts, 0, 1000001*sizeof(int)); // zeroe array

	// do counting
	startTimer();
	for(int iter = 0; iter < len; iter++)
	{
		counts[arr[iter]]++;
	}
    
	// do filling
	for(int iter = 0; iter < 1000001; iter++)
	{
        for(int rep = 0; rep < counts[iter]; rep++)
        {
            *arr = iter;
            arr++;
            totNumSwaps++;
        }
	}
	stopTimer();
    
    delete counts;
    
    sortsRun++;
}
