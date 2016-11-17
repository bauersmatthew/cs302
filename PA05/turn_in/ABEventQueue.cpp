#include "ABEventQueue.h"
#include <string.h>
#include <string>
#include <iostream>

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
	std::cerr << "(ABEQ) Allocating memory...\n";
	eventArray = new Event[capacity];
	cap = capacity;
	len = 0;

	std::cerr << "(ABEQ) Filling randomly...\n";
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
	if(len == cap)
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
	memmove(eventArray, &eventArray[1], (cap-1)*sizeof(Event));
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