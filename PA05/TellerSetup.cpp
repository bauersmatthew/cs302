#include "TellerSetup.h"
#include <stdarg.h>
#include <iostream>

// TELLERSETUP DEFS

void TellerSetup::printStats(std::ostream& out)
{
	out
		<< "Teller Setup: " << numLines << " Lines, " << numTellers << "Tellers\n"
		<< "\tAverage Simulation Time...\n"
		<< "\t\tCPU Time: " << totCPUTime/numTrials << " s\n"
		<< "\t\tVirtual Time: " << totVirtTime/numTrials << " units\n"
		<< "\tWait Times...\n"
		<< "\t\tAverage per Customer: " << totAvgWaitTime/numTrials << " units\n"
		<< "\t\tMaximum per Customer: " << totMaxWaitTime/numTrials << " units\n"
		<< "\tLine Lengths...\n"
		<< "\t\tAverage: " << totAvgLineLen/numTrials << "\n"
		<< "\t\tMaximum: " << totMaxLineLen/numTrials << "\n"
		<< "\tTotal Idle Time per Teller:\n";
		for(int teller = 0; teller < totIdleTimePerTeller.size(); teller++)
		{
			out << "Teller " << teller+1 << ": "
					<< totIdleTimePerTeller[teller] << "\n";
		}
		out << "\n";
}


// TELLER DEFS

Teller::Teller(EventQueue *ln, int *nc, int *twt, int *mwt)
{
	line = ln;
	numCustomers = nc;
	totWaitTime = twt;
	maxWaitTime = mwt;

	idleStart = 0;
	idleTime = 0;

	busy = false;
	busyUntil = 0;
}

void Teller::tick(int now)
{
	if(now == whenNext()) // ==> we have something to do now
	{
		if(busy) // ==> about to finish with customer
		{
			busy = false;
			(*numCustomers)++;
			idleStart = now;
		}
		else // ==> about to handle new customer
		{
			idleTime += (now - idleStart);

			Event customer = line->peekFront();
			line->popFront();

			*totWaitTime += (now - customer.arrival);
			*maxWaitTime = (now - customer.arrival) > *maxWaitTime ?
				(now - customer.arrival) : *maxWaitTime;

			busyUntil = now + customer.duration;
			busy  = true;
		}
	}
}

int Teller::whenNext()
{
	if(busy)
	{
		return busyUntil;
	}
	else
	{
		if(!line->isEmpty())
		{
			int arrvl = line->peekFront().arrival;
			// return idle start time if arrived while busy else arrival time
			if(arrvl < idleStart)
			{
				return idleStart;
			}
			else
			{
				return arrvl;
			}
		}
		else
		{
			return -1; // nothing coming up!
		}
	}
	// never gets here
}

void Teller::finish(int now)
{
	idleTime += (now - idleStart);
}


// TICKABLEQUEUE DEFS
TickableQueue::TickableQueue(EventQueue *evQ, long *tll, long *mll)
{
	eq = evQ;
	totLineLen = tll;
	maxLineLen = mll;
	lastTicked = 0;
}

void TickableQueue::regDestQueue(EventQueue *dest)
{
	destLines.push_back(dest);
}

void TickableQueue::tick(int now)
{
	// mark down queue length
	for(auto line : destLines)
	{
		*totLineLen += long((now-lastTicked)*line->length());
	}

	if(now == whenNext())
	{
		if(destLines.empty())
		{
			return; // shouldn't happen
		}
		// find the shortest dest queue
		EventQueue *shortest = destLines[0];
		for(auto line : destLines)
		{
			if(line->length() > shortest->length())
			{
				shortest = line;
			}
		}
		// insart
		shortest->addBack(eq->popFront());

		// check for max queue length
		if(shortest->length() > *maxLineLen)
		{
			*maxLineLen = shortest->length();
		}
	}
	lastTicked = now;
}

int TickableQueue::whenNext()
{
	if(eq->isEmpty())
	{
		return -1;
	}
	else
	{
		return eq->peekFront().arrival;
	}
}

// OTHER DEFS
int getEarliestTime(const std::vector<int>& times)
{
	int min = -1;
	for(auto time : times)
	{
		if(
			(min == -1) || (time != -1 && time < min)
			)
		{
			min = time;
		}
	}
	return min;
}