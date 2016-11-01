/**
 * @file PrecondViolatedExcept.cpp
 * @brief Implementation file for the PrecondViolatedExcept data type
 * @author Matthew Bauer
 * @details Implements the PrecondViolatedExcept data type
 * @Note Code taken from "Data Abstractions & Problem Solving with C++"
 * 	Seventh Edition by Frank Carrano and Timothy M.
 */

#include "PrecondViolatedExcept.h"

PrecondViolatedExcept::PrecondViolatedExcept(const std::string& message) : std::logic_error("Precondition Violated Exception: " + message)
{
}
