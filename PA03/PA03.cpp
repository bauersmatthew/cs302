/*
 * @file
 * @brief Implements the program entry point and i/o capabilities.
 * @author Matthew Bauer
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <sstream>
#include "FlightMap.v2.h"

/**
 * @brief Split the given string into parts by the given delimeter.
 * @param toSplit The string to split.
 * @param delim The delimeter.
 * @return A vector containing the parts of the string.
 */
std::vector<std::string> splitString(const std::string& toSplit, char delim)
{
	std::vector<std::string> parts;
	std::string currentPart;

	// loop through all chars in input string
	for(char curr : toSplit)
	{
		if(curr == delim)
		{
			// insert & reset
			parts.push_back(currentPart);
			currentPart = "";
		}
		else
		{
			// append to current part
			currentPart += curr;
		}
	}

	// make sure to include the last part (no delim at end)
	parts.push_back(currentPart);

	return parts;
}

/**
 * @brief Convert the given string into an int.
 * @param toConvert The string to convert.
 * @pre The given string can be converted into an integer.
 * @return The int value read fromt the given string.
 */
int stringToInt(const std::string& toConvert)
{
	int value;
	std::stringstream ss(toConvert);
	ss >> value;
	return value;
}

/**
 * @brief Load the file containing the list of cities.
 * @param path The path to the file.
 * @pre The given path points to a readable and correctly formatted file.
 * @return A vector of all the city names read from the file.
 */
std::vector<std::string> loadCities(const std::string& path)
{
	std::vector<std::string> cities;

	std::ifstream fin(path); // open file

	// read through one line at a time
	std::string line;
	while(std::getline(fin, line))
	{
		cities.push_back(line);
	}

	fin.close(); // close file

	return cities;
}

/**
 * @brief Load the file containing the flight paths.
 * @param path The path to the file.
 * @pre The given path points to a readable and correctly formatted file.
 * @return A map linking string pairs (i.e. ("Origin", "Destination")) to std::pairs
 *     of (flight number, flight cost).
 */
std::map<std::pair<std::string, std::string>, std::pair<int, int>>
	loadFlights(const std::string& path)
{
	std::map<std::pair<std::string, std::string>, std::pair<int, int>> flights;

	std::ifstream fin(path); // open file

	// read through line by line
	std::string line;
	while(std::getline(fin, line))
	{
		auto fields = splitString(line, '\t');
		// fields contains "Origin, Dest" | "num cost"

		std::vector<std::string> numFields = splitString(fields[1], ' ');
		// numFields contains "num" | "cost"

		std::vector<std::string> cityFields = splitString(fields[0], ',');
		cityFields[1].erase(0, 1); // remove space at beginning
		// cityFields contains "Origin" | "Dest"

		// for easier reading, put stuff into temp variables
		std::pair<std::string, std::string> cityPair(
			cityFields[0], cityFields[1]);
		std::pair<int, int> numPair(
			stringToInt(numFields[0]), stringToInt(numFields[1]));

		// put into map
		flights[cityPair] = numPair;
	}

	fin.close(); // close file

	return flights;
}

/**
 * @brief Load the file containing the flight requests.
 * @param path The path to the file.
 * @pre The given path points to a readable and correctly formatted file.
 * @return A vector containing ("Origin", "Destination") pairs.
 */
std::vector<std::pair<std::string, std::string>>
	loadRequests(const std::string& path)
{
	std::vector<std::pair<std::string, std::string>> requests;

	std::ifstream fin(path); // open file

	// read through line by line
	std::string line;
	while(std::getline(fin, line))
	{
		std::vector<std::string> cities = splitString(line, ',');
		cities[1].erase(0, 1); // remove space at beginning

		// insert
		requests.push_back(std::pair<std::string, std::string>(
			cities[0], cities[1]));
	}

	return requests;
}

/**
 * @brief Entry point.
 */
int main(int argc, char **argv)
{
	// process args
	std::string cityFile = "cityFile.txt";
	std::string flightFile = "flightFile.txt";
	std::string requestFile = "requestFile.txt";
	if(argc == 4)
	{
		cityFile = argv[1];
		flightFile = argv[2];
		requestFile = argv[3];
	}

	// open log file
	std::ofstream fout("HPAir.log.txt");

	// load files
	fout << "Loading files...\n";
	auto cities = loadCities(cityFile);
	auto flights = loadFlights(flightFile);
	auto requests = loadRequests(requestFile);

	// construct flight map
	// use V2 arbitrarily to demonstrate (although it should be a bit faster)
	fout << "Constructing flight map...\n";
	FlightMapV2 flightMap(cities, flights);

	// go through requests
	fout << "Processing requests...\n";
	std::string itinerary;
	for(auto req : requests)
	{
		std::cout
			<< "Request is to fly from "
			<< req.first
			<< " to "
			<< req.second
			<< ".\n";
		flightMap.isPath(req.first, req.second, itinerary, fout);
		std::cout << itinerary << "\n";
		itinerary = "";
	}

	fout.close();

	return 0;
}