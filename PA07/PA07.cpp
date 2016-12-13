/**
 * @file
 * @brief Main file for CS302/PA07
 * @author Matthew Bauer
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "RBTree.h"

/**
 * @brief Convert a boolean to a string.
 * @details Is a macro.
 * @param b The boolean to convert.
 */
#define B2S(b) (b?"TRUE":"FALSE")

/**
 * @brief Generate a set of test integers.
 * @details Generate 1000 integers, with values 1 to 10000.
 * @param testSet The vector to fill.
 */
void genTestSet(std::vector<int>& testSet)
{
    for(int iter = 0; iter < 1000; iter++)
    {
        testSet.push_back((rand()%10000)+1);
    }
}

/**
 * @breif Program entry point.
 */
int main()
{
    srand(time(0));

    std::vector<int> testSet;
    genTestSet(testSet);

    RBTree rbt;
    for(auto& val : testSet)
    {
        rbt.insert(val);
    }
    std::cout << "Tree height: " << rbt.getHeight() << "\n";
    std::cout << "Sum of all values: " << rbt.sum() << "\n\n";

    std::cout << "Empty (before clear): " << B2S(rbt.isEmpty()) << "\n";
    rbt.clear();
    std::cout << "Empty (after clear): " << B2S(rbt.isEmpty()) << "\n";

    return 0;
}
