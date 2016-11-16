#include "ABEventQueue.h"
#include <string.h>
#include <string>

ABEventQueue::ABEventQueue(int capacity)
{
	eventArray = new Event[capacity];
	cap = capacity;
	len = 0;
}

ABEventQueue::ABEventQueue(
	int capacity,
	int lobArrival, int hibArrival,
	int lobDuration, int hibDuration)
{
	eventArray = new Event[capacity];
	cap = capacity;
	len = 0;

	fillRandomly(capacity, lobArrival, hibArrival, lobDuration, hibDuration);
}

ABEventQueue::~ABEventQueue()
{
	delete[] eventArray;
}

int ABEventQueue::length()
{
	return len;
}

void ABEventQueue::addBack(Event newEv)
{
	if(len == capacity)
	{
		throw std::string("ABEQ full"); // this should never happen
	}
	eventArray[len++] = newEv;
}

Event ABEventQueue::popFront()
{
	if(isEmpty())
	{
		throw std::string("ABEQ empty"); // this should also never happen
	}
	Event front = eventArray[0];
	memmove(eventArray, &eventArray[1], (capacity-1)*sizeof(Event));
	len--;
	return front;
}

Event ABEventQueue::peekFront()
{
	if(isEmpty())
	{
		throw std::string("ABEQ empty");
	}
	return eventArray[0];
}