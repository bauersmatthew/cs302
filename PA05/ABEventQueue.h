/**
 * @file
 * @brief Declares the Array-Based Event Queue class.
 * @author Matthew Bauer
 */
#ifndef AB_EVENT_QUEUE_H
#define AB_EVENT_QUEUE_H

#include "EventQueue.h"

/**
 * @brief An Array-Based Event Queue
 * @details Capacity cannot change.
 */
class ABEventQueue : public EventQueue
{
	private:
		Event *eventArray;
		int cap;
		int len;

	public:
		/**
		 * @brief Constructs an empty queue with given capacity.
		 * @param capacity The capacity of the queue.
		 */
		ABEventQueue(int capacity);

		/**
		 * @brief Constructs a queue with given capacity and fills it randomly.
		 * @param capacity The capacity of the queue.
		 * @param lobArrival Passed to fillRandomly.
		 * @param hibArrival Passed to fillRandomly.
		 * @param lobDuration Passed to fillRandomly.
		 * @param hibDuration Passed to fillRandomly.
		 */
		ABEventQueue(
			int capacity,
			int lobArrival, int hibArrival,
			int lobDuration, int hibDuration);

		/**
		 * @copybrief EventQueue::~EventQueue
		 */
		~ABEventQueue();

		/**
		 * @copybrief EventQueue::length()
		 */
		int length();

		/**
		 * @copybrief EventQueue::addBack()
		 */
		void addBack(Event newEv);

		/**
		 * @copybrief EventQueue::popFront()
		 */
		Event popFront();

		/**
		 * @copybrief EventQueue::peekFront()
		 */
		Event peekFront();
};

#endif