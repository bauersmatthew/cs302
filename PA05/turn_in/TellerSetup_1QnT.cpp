#include "TellerSetup_1QnT.h"
#include "LLEventQueue.h"
#include <chrono>
#include <iostream>

using namespace std::chrono;

TellerSetup_1QnT::TellerSetup_1QnT(int n)
{
	numTrials = 0;

	totCPUTime = 0;
	totVirtTime = 0;

	totAvgWaitTime = 0;
	totMaxWaitTime = 0;
	totAvgLineLen = 0;
	totMaxLineLen = 0;

	numLines = 1;
	numTellers = n;
	totIdleTimePerTeller = std::vector<double>(n, 0);
}

void TellerSetup_1QnT::simulate(EventQueue *pEq)
{
	// timing
	high_resolution_clock::time_point start = high_resolution_clock::now();

	std::vector<Tickable*> toTick;

	std::cerr << "Setting up TickableQueue...\n";
	// set up tickablequeue; put in first
	double crTLL=0, crMLL=0;
	toTick.push_back(new TickableQueue(pEq, &crTLL, &crMLL));

	// set up 1 waitline
	std::cerr << "Setting up 1 waitline...\n";
	EventQueue *waitline = new LLEventQueue();
	((TickableQueue*)toTick[0])->regDestQueue(waitline);

	// set up tellers
	std::cerr << "Setting up tellers...\n";
	int crNC=0;
	double crTWT=0, crMWT=0;
	for(int tlr = 0; tlr < numTellers; tlr++)
	{
		toTick.push_back(new Teller(
			waitline, &crNC, &crTWT, &crMWT));
	}

	// run sim
	std::cerr << "Running siulation loop...\n";
	int oldNow=0, now=0;
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
	delete waitline;
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