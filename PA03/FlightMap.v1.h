/*
 * @file
 * @brief Interface for the FlightMap V1
 * @author Matthew Bauer
 * @note Heavily inspired by the textbook.
 */

#include <vector>
#include <string>
#include <fstream>
#include <stack>
#include <map>

/**
 * @brief Represents a v1 connection between cities.
 */
struct ConnectionV1
{
	std::string dest;
	int cost;
	int number;
};

/**
 * @brief Represents a v1 node in the city adjacency map.
 */
class CityNodeV1
{
public:
	std::string name;
	std::vector<ConnectionV1> connections;
	bool visited;

	/**
	 * @brief Initializes node with the given name.
	 * @param name The name of the city.
	 */
	CityNodeV1(const std::string& name);

	/**
	 * @brief Initializes node with empty name.
	 * @note Required for std::map compatibility.
	 */
	CityNodeV1();
};

/**
 * @brief Represents a v1 flight map.
 */
class FlightMapV1
{
	std::map<std::string, CityNodeV1> adjacencyMap;
	std::vector<std::string> cities;

	/**
	 * @brief Get the next unvisited city that connects to the given city.
	 * @param city The name of the current city.
	 * @return The name of the next city if one exists; otherwise, returns
	 *     an empty string.
	 */
	std::string getUnvisitedConnection(const std::string& city);

	/**
	 * @brief Generate a flight itinerary given the city stack.
	 * @param cityStack The stack of city names describing the flight path.
	 * @pre The given stack is not empty.
	 * @return The flight itinerary string.
	 * @note Overwrites cityStack!
	 */
	std::string generateItinerary(std::stack<std::string>& cityStack);

public:
	/**
	 * @brief Initializes the flight map.
	 * @param cities A list of all cities.
	 * @param flights A list of all flights.
	 */
	FlightMapV1(
		std::vector<std::string> cities,
		std::map<std::pair<std::string, std::string>, std::pair<int, int>> flights);

	/**
	 * @brief Mark a city as visited.
	 * @param city The name of the city to mark as visited.
	 * @pre The given city is registered in the map.
	 */
	void markVisited(const std::string& city);

	/**
	 * @brief Mark all cities as not visited.
	 */
	void unvisitAll();

	/**
	 * @brief Test whether a sequence of flights exists between two cities.
	 * @param origin The name of the origin city.
	 * @param dest The name of the destination city.
	 * @param itinerary The itenarary output of the path found.
	 * @param log The log to write log (debug) output to.
	 * @return True if a sequence exists; false otherwise.
	 */
	bool isPath(
		const std::string& origin, const std::string& dest,
		std::string& itinerary, std::ofstream& log);

};