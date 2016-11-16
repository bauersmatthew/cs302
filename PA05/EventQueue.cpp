#include "EventQueue.h"
#include <cstdlib>
#include <algorithm>

// EventQueue defs
bool EventQueue::isEmpty()
{
	return (length() == 0);
}

void EventQueue::fillRandomly(
	int num,
	int lobArrival, int hibArrival,
	int lobDuration, int hibDuration)
{
	std::vector<Event> events; // temporary, sortable storage

	// generate in random order
	for(num--)
	{
		Event newEv;
		newEv.arrival = (rand()%(hibArrival-lobArrival+1))+lobArrival;
		newEv.duration = (rand()%(hibDuration-lobDuration+1))+lobDuration;
		events.push_back(newEv);
	}

	auto cmpEvs = [](Event e1, Event e2){
		return e1.arrival < e2.arrival ? -1 : e1.arrival > e2.arrival ? 1 : 0};
	std::sort(events.begin(), events.end(), cmpEvs);

	for(Event ev : events)
	{
		addBack(ev);
	}
}