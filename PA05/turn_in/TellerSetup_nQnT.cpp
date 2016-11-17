#include "TellerSetup_nQnT.h"
#include "LLEventQueue.h"
#include <chrono>

using namespace std::chrono;

TellerSetup_nQnT::TellerSetup_nQnT(int n)
{
	totCPUTime = 0;
	totVirtTime = 0;

	totAvgWaitTime = 0;
	totMaxWaitTime = 0;
	totAvgLineLen = 0;
	totMaxLineLen = 0;

	numTellers = numLines = n;
	totIdleTimePerTeller = std::vector<double>(n, 0);
}

void TellerSetup_nQnT::simulate(EventQueue *pEq)
{
	// timing
	high_resolution_clock::time_point start = high_resolution_clock::now();

	std::vector<Tickable*> toTick;

	// set up tickablequeue; put in first
	std::cerr << "Setting up TickableQueue...\n";
	double crTLL=0, crMLL=0;
	toTick.push_back(new TickableQueue(pEq, &crTLL, &crMLL));

	// set up n waitlines
	std::cerr << "Setting up waitlines...\n";
	std::vector<EventQueue*> waitlines;
	for(int iter = 0; iter < numLines; iter++)
	{
		waitlines.push_back(new LLEventQueue());
		((TickableQueue*)toTick[0])->regDestQueue(waitlines[iter]);
	}

	// set up tellers
	std::cerr << "Setting up tellers...\n";
	int crNC=0;
	double crTWT=0, crMWT=0;
	for(int tlr = 0; tlr < numTellers; tlr++)
	{
		toTick.push_back(new Teller(waitlines[tlr], &crNC, &crTWT, &crMWT));
	}

	// run sim
	std::cerr << "Running simulation loop...\n";
	int oldNow = 0;
	int now = 0;
	while(true)
	{
		// get next event time
		std::vector<int> times;
		for(auto tckbl : toTick)
		{
			times.push_back(tckbl->whenNext());
		}
		now = getEarliestTime(times);

		if(now == -1)
		{
			std::cerr << "Exiting simulation loop...\n";
			// finish sim
			for(int iter = 1; iter < toTick.size(); iter++)
			{
				((Teller*)toTick[iter])->finish(oldNow);
			}
			break;
		}

		// do ticking
		for(auto tckbl : toTick)
		{
			tckbl->tick(now);
		}

		oldNow = now;
	}

	// save stats
	std::cerr << "Saving stats...\n";
	totCPUTime +=
		duration_cast<duration<double>>(
		high_resolution_clock::now() - start).count();
	totVirtTime += oldNow;
	totAvgWaitTime += crTWT/double(crNC);
	totMaxWaitTime += crMWT;
	totAvgLineLen += crTLL/double(oldNow*numLines);
	totMaxLineLen += crMLL;

	// clean up
	std::cerr << "Cleaning up...\n";
	for(auto wl : waitlines)
	{
		delete wl;
	}
	for(int iter = 0; iter < toTick.size(); iter++)
	{
		if(iter >= 1)
		{
			// tellers only: save idle time
			totIdleTimePerTeller[iter-1] += ((Teller*)toTick[iter])->idleTime;
		}
		delete toTick[iter];
	}

	numTrials++;
}