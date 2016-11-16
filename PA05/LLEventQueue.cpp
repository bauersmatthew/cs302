#include "LLEventQueue.h"
#include <string>

LLEventQueue::LLEventQueue()
{
	head = tail = nullptr;
	len = 0;
}

LLEventQueue::LLEventQueue(
	int num,
	int lobArrival, int hibArrival,
	int lobDuration, int hibDuration)
{
	head = tail = nullptr;
	len = 0;
	fillRandomly(num, lobArrival, hibArrival, lobDuration, hibDruation);
}

LLEventQueue::~LLEventQueue()
{
	while(!isEmpty())
	{
		popFront();
	}
}

int LLEventQueue::length()
{
	return len;
}

void LLEventQueue::addBack(Event newEv)
{
	len++;
	if(!head) // empty
	{
		// construct head and tail as same node
		head = tail = new LLEQNode;
		head->next = nullptr; // DO NOT LOOP HEAD TO TAIL
		tail->ev = newEv;
	}
	else
	{
		tail->next = new LLEQNode;
		tail->next->ev = newEv;
		tail->next->next = nullptr;
	}
}

Event LLEventQueue::popFront()
{
	if(isEmpty())
	{
		throw std::string("LLEQ empty"); // should never get here
	}
	len--;
	LLEQNode *toRem = head;
	Event frontVal = toRem->ev;
	head = head->next;
	delete toRem;
	return frontVal;
}

Event LLEventQueue::peekFront()
{
	if(isEmpty())
	{
		throw std::string("LLEQ empty");
	}
	return head->ev;
}