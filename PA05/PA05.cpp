/**
 * @file
 * @brief Main file for CS302/PA05
 * @author Matthew Bauer
 */
#include <fstream>
#include "Event.h"
#include "ABEventQueue.h"
#include "LLEventQueue.h"
#include "TellerSetup_1QnT.h"
#include "TellerSetup_nQnT.h"

/**
 * @brief The number of events to use per simulation.
 */
const int NUM_EVENTS = 99999;

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
		setup->simulate(ABEventQueue(NUM_EVENTS));
	}
	setup->printStats(out);
}

/**
 * @brief Program entry point.
 */
int main()
{
	std::ofstream fout("stats.txt");

	// do tests
	// 1 queue 1 teller
	TellerSetup_1QnT ts1Q1T(1);
	TestSetup(&ts1Q1T, fout);

	// 3 queues 3 tellers
	TellerSetup_nQnT ts3Q3T(3);
	TestSetup(&ts3Q3T, fout);

	// 1 queue 3 tellers
	TellerSetup_1QnT ts1Q3T(3);
	TestSetup(&ts1Q3T, fout);

	fout.close();
	return 0;
}