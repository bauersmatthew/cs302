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
	totIdleTimePerTeller = std::vector<float>(n, 0);
}

void TellerSetup_nQnT::simulate(EventQueue *pEq)
{
	// timing
	high_resolution_clock::time_point start = high_resolution_clock::now();

	std::vector<Tickable*> toTick;

	// set up tickablequeue; put in first
	long crTLL=0, crMLL=0;
	toTick.push_back(new TickableQueue(pEq, &crTLL, &crMLL));

	// set up n waitlines
	std::vector<EventQueue*> waitlines;
	for(int iter = 0; iter < numlines; iter++)
	{
		waitlines.push_back(new LLEventQueue());
		toTick[0]->regDestQueue(waitlines[iter]);
	}

	// set up tellers
	int crNC=0, crTWT=0, crMWT=0;
	for(int tlr = 0; tlr < numTellers; tlr++)
	{
		toTick.push_back(new Teller(waitlines[tlr], &crNC, &crTWT, &crMWT));
	}

	// run sim
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
	totCPTime +=
		duration_cast<duration<<double>>(
		high_resolution_clock::now() - start).count();
	totVirtTime += oldNow;
	totAvgWaitTime += float(crTWT)/float(crNC);
	totMaxWaitTime += crMWT;
	totAvgLineLen += float(crTLL)/float(oldNow*numLines);
	totMaxLineLen += crMLL;

	// clean up
	for(auto wl : waitlines)
	{
		delete wl;
	}
	for(int iter = 0; iter < toTick.size(); iter++)
	{
		if(iter >= 1)
		{
			// tickers only: save idle time
			totIdleTimePerTeller[iter-1] += ((Ticker*)toTick[iter])->idleTime;
		}
		delete toTick[iter];
	}
}