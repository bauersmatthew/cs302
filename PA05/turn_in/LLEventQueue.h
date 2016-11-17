/**
 * @file
 * @brief Declares the Linked-List-Based Event Queue class.
 * @author Matthew Bauer
 */
#ifndef LL_EVENT_QUEUE_H
#define LL_EVENT_QUEUE_H

#include "EventQueue.h"

/**
 * @brief A node in an LLEventQueue
 */
struct LLEQNode
{
	Event ev;
	LLEQNode *next;
};

/**
 * @brief A Linked-List-Based Event Queue
 */
class LLEventQueue : public EventQueue
{
public:
	LLEQNode *head;
	LLEQNode *tail;
	int len;

public:
	/**
	 * @brief Constructs an empty queue.
	 */
	LLEventQueue();

	/**
	 * @brief Constructs a queue and fills it randomly.
	 * @param num Passed to fillRandomly.
	 * @param lobArrival Passed to fillRandomly.
	 * @param hibArrival Passed to fillRandomly.
	 * @param lobDuration Passed to fillRandomly.
	 * @param hibDuration Passed to fillRandomly.
	 */
	LLEventQueue(
		int num,
		int lobArrival, int hibArrival,
		int lobDuration, int hibDuration);

	/**
	 * @copybrief EventQueue::~EventQueue
	 */
	~LLEventQueue();

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