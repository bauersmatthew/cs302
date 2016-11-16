/**
 * @file
 * @brief Main file for CS302/PA05
 * @author Matthew Bauer
 */
#include <fstream>
#include <iostream>
#include "Event.h"
#include "ABEventQueue.h"
#include "LLEventQueue.h"
#include "TellerSetup_1QnT.h"
#include "TellerSetup_nQnT.h"

/**
 * @brief The number of events to use per simulation.
 */
const int NUM_EVENTS = 99999;
const int MIN_ARRIVAL = 0;
const int MAX_ARRIVAL = 100000;
const int MIN_DURATION = 1;
const int MAX_DURATION = 100;

/**
 * @brief Test the given TellerSetup on 10 samples.
 * @details Uses array-based queues.
 * @param pEvQ A pointer to the EventQueue to test.
 * @param out The stream to send output to.
 */
void TestSetup(TellerSetup *setup, std::ostream& out)
{
	for(int rep = 0; rep < 10; rep++)
	{
		std::cerr << "Generating queue...\n";
		EventQueue *eq = new ABEventQueue(
			NUM_EVENTS,
			MIN_ARRIVAL, MAX_ARRIVAL,
			MIN_DURATION, MAX_DURATION);
		std::cerr << "Starting simulation...\n";
		setup->simulate(eq);
		std::cerr << "Simulation finished.\n";
		delete eq;
	}
	std::cerr << "Printing stats...\n";
	setup->printStats(out);
	std::cerr << "\n\n";
}

/**
 * @brief Program entry point.
 */
int main()
{
	std::cerr << "Opening file...\n";
	std::ofstream fout("stats.txt");

	// do tests
	// 1 queue 1 teller
	std::cerr << "Testing: 1Q1T...\n";
	TellerSetup_1QnT ts1Q1T(1);
	TestSetup(&ts1Q1T, fout);

	// 3 queues 3 tellers
	std::cerr << "Testing: 3Q3T...\n";
	TellerSetup_nQnT ts3Q3T(3);
	TestSetup(&ts3Q3T, fout);

	// 1 queue 3 tellers
	std::cerr << "Testing: 1Q3T...\n";
	TellerSetup_1QnT ts1Q3T(3);
	TestSetup(&ts1Q3T, fout);

	fout.close();
	return 0;
}