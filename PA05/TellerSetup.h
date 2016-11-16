/**
 * @file
 * @brief Declares the TellerSetup abstract class.
 * @author Matthew Bauer
 */
#ifndef TELLER_SETUP_H
#define TELLER_SETUP_H

#include <iostream>
#include <vector>
#include "EventQueue.h"

class TellerSetup
{
protected:
	// floats to make math easier later
	float numTrials;

	float totCPUTime;
	float totVirtTime;

	float totAvgWaitTime;
	float totMaxWaitTime;

	float totAvgLineLen;
	float totMaxLineLen;

	std::vector<float> totIdleTimePerTeller;

	int numTellers;
	int numLines;

public:
	/**
	 * @brief Run the simulation (1 trial).
	 * @param pEq Pointer to the EventQueue of events to feed the simulation.
	 */
	virtual void simulate(EventQueue *pEq) =0;

	/**
	 * @brief Output setup stats.
	 * @param out The stream to write to.
	 */
	void printStats(std::ostream& out);

};

/**
 * @brief A Tickable object.
 * @details For use by TellerSetup.
 */
class Tickable
{
public:
	/**
	  * @brief Do one tick at the given time.
	  * @param now The current time.
	  */
	virtual void tick(int now) =0;

	/**
	 * @brief Get when this tickable needs to be ticked next.
	 * @details Returns -1 when there is no future event.
	 * @return When this tickable needs to be ticked next.
	 */
	virtual int whenNext() =0;
};

/**
 * @brief Models a bank teller.
 * @details For use by TellerSetup.
 */
class Teller : public Tickable
{
protected:
	EventQueue *line;

	int *numCustomers;

	int *totWaitTime;
	int *maxWaitTime;

	int idleStart;

	bool busy;
	int busyUntil;

public:
	int idleTime;

	/**
	 * @brief Construct a Teller with given stat vars and source line.
	 * @param ln The line to draw customers from.
	 * @param nc Pointer to the customer counter.
	 * @param twt Pointer to the wait time counter.
	 * @param mwt Pointer to the max wait time.
	 */
	Teller(EventQueue *ln, int *nc, int *twt, int *mwt);

	/**
	 * @copybrief Tickable::tick()
	 */
	void tick(int now);

	/**
	 * @copybrief Tickable::whenNext()
	 */
	int whenNext();

	/**
	 * @brief Finishes the Teller model. Should be called at sim end.
	 * @param now The last tick.
	 */
	void finish(int now);
};

/**
 * @brief An EventQueue wrapper that enables tick functionality.
 * @details An EventQueue wrapper that can be "ticked".
 */
class TickableQueue : public Tickable
{
private:
	EventQueue *eq;
	std::vector<EventQueue*> destLines;

	long *totLineLen;
	long *maxLineLen;

	int lastTicked;

public:
	/**
	 * @brief Constructs a TickableQueue around the given EventQueue
	 * @param evQ The EventQueue to wrap.
	 * @param tll Pointer to the total line length over time counter.
	 * @param mll Pointer to the max line length counter.
	 */
	TickableQueue(EventQueue *evQ, long *tll, long *mll);

	/**
	 * @brief Register a destination queue for this queue to feed into.
	 * @param dest The queue to register.
	 */
	void regDestQueue(EventQueue *dest);

	/**
	 * @copybrief Tickable::tick()
	 */
	void tick(int now);

	/**
	 * @copybrief Tickable::whenNext()
	 */
	int whenNext();

};

/**
 * @brief Take the min of the given numbers, with -1 values excluded.
 * @details For use by TellerSetup.
 * @param times The times.
 */
int getEarliestTime(const std::vector<int>& times);

#endif