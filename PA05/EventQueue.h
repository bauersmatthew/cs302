/**
 * @file
 * @brief Declares the EventQueue abstract class.
 * @author Matthew Bauer
 */
#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include "Event.h"

class EventQueue
{
public:
	/**
	 * @brief Cleans up the queue.
	 */
	virtual ~EventQueue() =0;

	/**
	 * @brief Get the length of the queue.
	 * @return The length of the queue.
	 */
	virtual int length() =0;

	/**
	 * @brief Get whether the queue is empty.
	 * @return True if empty; false otherwise.
	 */
	bool isEmpty();

	/**
	 * @brief Fills the queue with randomly generated events.
	 * @brief num The number of events to generate.
	 * @param lobArrival The low bound for arrival times.
	 * @param hibArrival The high bound for arrival times.
	 * @param lobDuration The low bound for duration times.
	 * @param hibDuration The high bound for duration times.
	 */
	void fillRandomly(
		int num,
		int lobArrival, int hibArrival,
		int lobDuration, int hibDuration);

	/**
	 * @brief Adds to the back of the queue.
	 * @param newEv The event to add.
	 */
	virtual void addBack(Event newEv) =0;

	/**
	 * @brief Get and remove the event at the front of the queue.
	 * @return The event at the front of the queue.
	 */
	virtual Event popFront() =0;

	/**
	 * @brief Peek at the front of the queue.
	 * @return The event at the front of the queue.
	 */
	virtual Event peekFront() = 0;
};

#endif