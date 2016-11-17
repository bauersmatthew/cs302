/**
 * @file
 * @brief Declares a TellerSetup with 1 Queue and N Tellers.
 * @author Matthew Bauer
 */
#ifndef TELLER_SETUP_1QNT_H
#define TELLER_SETUP_1QNT_H

#include "TellerSetup.h"

class TellerSetup_1QnT : public TellerSetup
{
public:
	/**
	 * @brief Constructs a 1QnT Teller Setup with given n.
	 * @param n The number of tellers.
	 */
	TellerSetup_1QnT(int n);

	/**
	 * @copybrief TellerSetup::simulate()
	 */
	void simulate(EventQueue *pEq);
};

#endif