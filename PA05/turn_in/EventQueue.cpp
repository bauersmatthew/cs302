#include "EventQueue.h"
#include <cstdlib>
#include <algorithm>
#include <iostream>

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
	std::cerr << "(EQ) Generating events...\n";
	while(num--)
	{
		Event newEv;
		newEv.arrival = (rand()%(hibArrival-lobArrival+1))+lobArrival;
		newEv.duration = (rand()%(hibDuration-lobDuration+1))+lobDuration;
		events.push_back(newEv);
	}

	std::cerr << "(EQ) Sorting generated events...\n";
	auto cmpEvs = [](Event e1, Event e2){
		return e1.arrival >= e2.arrival ? false : true;};
	std::sort(events.begin(), events.end(), cmpEvs);

	std::cerr << "(EQ) Adding generated events to queue...\n";
	for(Event ev : events)
	{
		addBack(ev);
	}
}

EventQueue::~EventQueue(){}