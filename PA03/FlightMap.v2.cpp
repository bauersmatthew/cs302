#include "FlightMap.v2.h"

// helper functions
bool strInVec(const std::vector<std::string>& vec, const std::string& toFind)
{
	for(auto str : vec)
	{
		if(str == toFind)
		{
			return true;
		}
	}
	return false;
}

void logStackState(const std::stack<std::string>& stack, std::ofstream& log)
{
	std::string top = "(empty)";
	if(!stack.empty())
	{
		top = stack.top();
	}

	log << "STACK TOP: " << top << "    SIZE: " << stack.size();
	log << "\n";
}

// citynode defs
CityNodeV2::CityNodeV2(const std::string& name)
{
	this->name = name;
	visited = false;
	tryNext = 0;
}
CityNodeV2::CityNodeV2()
{
	name = "";
	visited = false;
	tryNext = 0;
}

// flightmap defs
FlightMapV2::FlightMapV2(
		std::vector<std::string> cities,
		std::map<std::pair<std::string, std::string>, std::pair<int, int>> flights)
{
	// fill map with blank (unconnected) nodes
	for(auto cityName : cities)
	{

		adjacencyMap[cityName] = CityNodeV2(cityName);
	}

	// add connections
	for(auto iter = flights.begin(); iter != flights.end(); ++iter)
	{
		// fill out connection
		ConnectionV2 connection;
		connection.dest = iter->first.second;
		connection.number = iter->second.first;
		connection.cost = iter->second.second;

		// store connection
		adjacencyMap[iter->first.first].connections.push_back(connection);
	}

	// save cities array
	this->cities = cities;
}

void FlightMapV2::markVisited(const std::string& city)
{
	adjacencyMap[city].visited = true;
}

void FlightMapV2::unvisitAll()
{
	for(auto iter = adjacencyMap.begin(); iter != adjacencyMap.end(); ++iter)
	{
		iter->second.visited = false;
		iter->second.tryNext = 0;
	}
}

bool FlightMapV2::isPath(
	const std::string& origin, const std::string& dest, std::string& itinerary,
	std::ofstream& log)
{
	// check that both dest and origin are serviced
	if(!strInVec(cities, origin))
	{
		itinerary += "Sorry. HPAir does not serve ";
		itinerary += origin;
		itinerary += ".\n";
		return false;
	}
	else if(!strInVec(cities, dest))
	{
		itinerary += "Sorry. HPAir does not serve ";
		itinerary += dest;
		itinerary += ".\n";
		return false;
	}

	std::stack<std::string> cityStack;
	unvisitAll();

	log << "\n--------\n\n";

	cityStack.push(origin);
	markVisited(origin);

	logStackState(cityStack, log);

	std::string topCity = cityStack.top();
	while(!cityStack.empty() && topCity != dest)
	{
		// try to go to next city
		std::string next = getUnvisitedConnection(topCity);
		if(next.empty())
		{
			// none found; backtrack
			cityStack.pop();
			log << "Backtracking...\n";
		}
		else
		{
			// one found; go there
			cityStack.push(next);
			markVisited(next);
			log << "Going forward...\n";
		}
		logStackState(cityStack, log);

		// update top city
		if(!cityStack.empty())
		{
			topCity = cityStack.top();
		}
	}

	// if empty, no route found; othrwise, a route was found.
	bool routeFound = !cityStack.empty();

	if(!routeFound)
	{
		// put sorry message in itinerary
		itinerary = "Sorry. HPAir does not fly from ";
		itinerary += origin;
		itinerary += " to ";
		itinerary += dest;
		itinerary += ".\n";
	}
	else
	{
		// generate itinerary before returning
		itinerary = generateItinerary(cityStack);
	}

	return routeFound;
}

std::string FlightMapV2::getUnvisitedConnection(const std::string& city)
{
	// check that city is registered
	// invoked when requested start city was not in list of cities.
	if(adjacencyMap.find(city) == adjacencyMap.end())
	{
		return ""; // not found
	}

	for(
		;
		adjacencyMap[city].tryNext < adjacencyMap[city].connections.size();
		adjacencyMap[city].tryNext++)

	{
		std::string next =
			adjacencyMap[city].connections[adjacencyMap[city].tryNext].dest;

		if(!adjacencyMap[next].visited)
		{
			adjacencyMap[city].tryNext++;
			return next;
		}
	}
	return "";
}

std::string FlightMapV2::generateItinerary(std::stack<std::string>& cityStack)
{
	std::string itinerary = "";
	int totalCost = 0;

	// reverse the stack
	std::stack<std::string> revStack;
	while(!cityStack.empty())
	{
		revStack.push(cityStack.top());
		cityStack.pop();
	}

	// go in pairs
	std::string orig = revStack.top();
	revStack.pop();
	std::string dest = revStack.top();
	while(!revStack.empty())
	{
		// find relevant connection
		ConnectionV2 relevantConnection;
		for(auto connect : adjacencyMap[orig].connections)
		{
			if(connect.dest == dest)
			{
				relevantConnection = connect;
				break;
			}
		}

		// add details to string
		itinerary += "Flight #";
		itinerary += std::to_string(relevantConnection.number);
		itinerary += " from ";
		itinerary += orig;
		itinerary += " to ";
		itinerary += dest;
		itinerary += "\tCost: $";
		itinerary += std::to_string(relevantConnection.cost);
		itinerary += "\n";

		// add to total cost
		totalCost += relevantConnection.cost;

		// go on to the next flight
		revStack.pop();
		if(revStack.empty())
		{
			break;
		}
		else
		{
			orig = dest;
			dest = revStack.top();
		}
	}

	// append total cost information
	itinerary += "Total Cost ........ $";
	itinerary += std::to_string(totalCost);
	itinerary += "\n";

	return itinerary;
}