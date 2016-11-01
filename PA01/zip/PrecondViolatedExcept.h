/**
 * @file PrecondViolatedExcept.h
 * @brief Interface file for the PrecondViolatedExcept data type
 * @author Matthew Bauer
 * @details Specifies the interface of the PrecondViolatedExcept
 * 	data type
 * @Note Specification taken from "Data Abstractions & Problem Solving
 * 	with C++" Seventh Edition by Frank Carrano and Timothy M.;
 * 	doxygen comments written by Matthew Bauer (student).
 */

#ifndef _PRECOND_VIOLATED_EXCEPT
#define _PRECOND_VIOLATED_EXCEPT

#include <stdexcept>
#include <string>

class PrecondViolatedExcept : public std::logic_error
{
public:
	/**
	 * @brief Construct a PrecondViolatedExcept with the given
	 * 	message.
	 * @post The constructed object's message will match the one
	 * 	specified by the message parameter.
	 * @param message The message to be held.
	 */
	PrecondViolatedExcept(const std::string& message = "");
};

#endif
