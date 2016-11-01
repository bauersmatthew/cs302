/**
 * @file
 * @author
 * @brief Implementation file for basic sorting structures.
 */
#include "Sorter.h"

// sorter defs
Sorter::Sorter()
{
	name = "Base Sorter";
	resetStats(); // redundant, but here for clarity/verbosity/safety
}

SortStats Sorter::getStats()
{
	SortStats stats;
	float fltSortsRun = (float)sortsRun; // for convenience

	stats.avgTime = float(totTime)/fltSortsRun;
	stats.avgNumComparisons = float(totNumComparisons)/fltSortsRun;
	stats.avgNumSwaps = float(totNumSwaps)/fltSortsRun;

	return stats;
}

void Sorter::resetStats()
{
	sortsRun = 0;
	totTime = 0;
	totNumComparisons = 0;
	totNumSwaps = 0;
}

std::string Sorter::getName()
{
	return name;
}

void Sorter::startTimer()
{
	tmrStart = std::chrono::high_resolution_clock::now();
}
void Sorter::stopTimer()
{
	totTime += std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now()-tmrStart).count();
}