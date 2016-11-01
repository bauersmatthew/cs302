/**
 * @file
 * @brief Implements the program entry point.
 * @author Matthew Bauer
 * @Note File skeleton created by Shehryar Khattak for CS302 Spring 2016.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

/**
 * @brief Returns the kth smallest value in an arrray.
 * @param kVal The value of k.
 * @param array The array to search. WARNING: is edited by the function.
 * @param first The first item in the section of the array to search.
 * @param last The last item in the section of the array to search.
 * @param log The string to write the algorithm log into.
 * @pre last-first+1 >= k_val
 * @pre log == ""
 * @post The log parameter will be filled with a log report.
 * @return The kth smallest value in the given array.
 */
int kSmall(int kVal, int *array, int first, int last, std::string& log)
{
	// choose the first value to be the pivot -- arbitrary
	int pivotIndex = first;
	int pivot = array[pivotIndex];

	// write log header
	if(log == "")
	{
		log += "Format: a,b,c,[pivot],d,e,f\n";
		log += "\tE.g.\t0,1,2,[4],6,7,8\n\n";
	}
	
	// partition around the pivot
	for(
		int currValIndex = first+1;
		currValIndex <= last;
		currValIndex++)
	{
		int currVal = array[currValIndex];
		if(currVal < pivot)
		{
			// move curr_val before pivot
			memmove(
				array+pivotIndex+1, // shift one right
				array+pivotIndex, // source = memory in [PIVOT, CURR)
				sizeof(int)*(currValIndex-pivotIndex));
			array[pivotIndex] = currVal;

			// update indices accordingly
			pivotIndex += 1;
			//curr_val_index += 1; // increment extra because the pivot moved
		}
	}

	// write to log
	for(int index=first; index <= last; index++)
	{
		if(index == pivotIndex)
		{
			log += "[";
		}
		log += std::to_string(array[index]);
		if(index == pivotIndex)
		{
			log += "]";
		}
		log += ",";
	}
	log[log.length()-1] = '\n'; // replace trailing comma with newline

	// do recursive decision-making
	if(kVal < pivotIndex - first + 1)
	{
		// next time search only the section left of pivot
		return kSmall(kVal, array, first, pivotIndex-1, log);
	}
	else if(kVal > pivotIndex - first + 1)
	{
		// next time search only the section right of pivot
		return kSmall(
			kVal-(pivotIndex-first+1), array, pivotIndex+1, last, log);
	}
	else
	{
		// base case
		return pivot;
	}
}

/**
 * @brief Entry point/main function of the program.
 */
int main(int argc, char **argv){

	//Declerations (insert as needed)
	int kSmall_pos;			//For User Input
	int kSmall_val=0;		//Populate using your algorithm implementation

	std::string inputFile = "data2.txt"; // file to load the numbers from
	std::string logFile = "log.txt"; // file to write log to
	if(argc >= 2)
	{
		inputFile = argv[1];
	}
	if(argc >= 3)
	{
		logFile = argv[2];
	}

	//User Input DO NOT MODIFY
	std::cout<<"Please enter required kth smallest value:";
	std::cin>>kSmall_pos;


	//File Read code (insert) - This code should be able to parse the data in a text file similar to the provided one and store values in an array for processing.
	int *array = new int[100];
	int size = 0;
	int capacity = 100;
	std::ifstream fin(inputFile);

	// prime loop
	int tmpInt;
	fin >> tmpInt;
	// loop
	while(fin)
	{
		// check array has space
		if(size == capacity)
		{
			// increase capacity of array
			capacity += 100;
			int *newArray = new int[capacity];
			memcpy(newArray, array, size*sieof(int));
			delete array;
			array = newArray;
		}

		// store value
		array[size] = tmpInt;
		size++;

		fin >> tmpInt;
	}
	fin.close();

	// validate user input
	if(kSmall_pos < 1 || kSmall_pos > size-1+1)
	{
		std::cerr << "Sorry, the given input was invalid." << std::endl;
		delete array;
		return -1;
	}


	//kmsall algorithm implementation or function call (insert) - implement using recursion as indicated
	std::string log = "";
	kSmall_val = kSmall(kSmall_pos, array, 0, size-1, log);
	delete array;


	//Log file output (insert) - preferred in .txt format acoording to instructions posted on assignment page
	std::ofstream fout(logFile);
	fout << log;
	fout.close();


	//Output DO NOT MODIFY
	std::cout<<"kth smallest value = "<<kSmall_val<<std::endl;

	return 0;
}
