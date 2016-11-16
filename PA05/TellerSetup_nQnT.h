/**
 * @file
 * @brief Declares a TellerSetup with N Queues and N Tellers.
 * @author Matthew Bauer
 */
#ifndef TELLER_SETUP_NQNT_H
#define TELLER_SETUP_NQNT_H

#include "TellerSetup.h"

class TellerSetup_nQnT : public TellerSetup
{
public:
	/**
	 * @brief Constructs a nQnT Teller Setup with given n.
	 * @param n The number of tellers and queues.
	 */
	TellerSetup_nQnT(int n);

	/**
	 * @copybrief TellerSetup::simulate()
	 */
	void simulate(EventQueue *pEq);
};

#endif