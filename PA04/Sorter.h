/**
 * @file
 * @author Matthew Bauer
 * @brief Declaration file for basic sorting structures.
 */
#ifndef SORTER_H
#define SORTER_H

#include <string>
#include <chrono>

/**
 * @brief Contains sorting statistics.
 */
struct SortStats
{
	float avgTime;
	float avgNumComparisons;
	float avgNumSwaps;
};

/**
 * @brief Base class for Sorter classes, which sort int data.
 * @details Sorter classes record various statistics on the sort.
 */
class Sorter
{
protected:
	int sortsRun; // the number of datasets sorted
	long totTime; // the total number of CPU time
	long totNumComparisons; // the total number of comparisons
	long totNumSwaps; // the total number of swaps
	std::string name; // the name of the sorter

	// for use by startTimer and stopTimer
	std::chrono::time_point<std::chrono::high_resolution_clock> tmrStart;
	
	/**
	 * @brief Starts timing the algorithm.
	 * @pre The timer is stopped.
	 */
	void startTimer();

	/**
	 * @brief Stops timing the algorithm and adds the elapsed time to totTime.
	 * @pre The timer has been started.
	 */
	void stopTimer();

public:

	/**
	 * @brief Default constructor for Sorters.
	 * @details Constructs with name: "Base Sorter"
	 */
	Sorter();
	// default copy constructor, destructor ok.

	/**
	 * @brief Sorts an array in place.
	 * @param arr The array to sort.
	 * @param len The length of the array to sort.
	 * @pre The given array is at least len long.
	 * @details Algorithm is abstracted.
	 */
	virtual void sortInPlace(int *arr, int len) = 0;

	/**
	 * @brief Returns statistics on all sorts performed.
	 * @return A filled SortStats instance.
	 */
	SortStats getStats();

	/**
	 * @brief Resets the stats.
	 */
	void resetStats();

	/**
	 * @brief Gets the name of this sorter.
	 * @return The name of this sorter.
	 */
	std::string getName();
};

#endif
