/**
 * @file
 * @brief Main file for CS302/PA06.
 * @author Matthew Bauer
 */

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "BinSearchTree.h"
#include "BSTOStream.h"

/**
 * @brief Get whether a given value is contained in a given vector.
 * @param val The value to search for.
 * @param vec The vector to search in.
 * @return Whether val is contained in vec.
 */
bool vecContains(int val, const std::vector<int>& vec)
{
    for(int num : vec)
    {
        if(val == num)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Generate a set of unique random integers 1-200 with given length.
 * @param num The length of the set to generate.
 * @return The generated set.
 */
std::vector<int> genRandset(int num)
{
    std::vector<int> set;
    while(num--)
    {
        int nxtVal = (rand()%200)+1;
        while(vecContains(nxtVal, set))
        {
            nxtVal = (rand()%200)+1;
        }
        set.push_back(nxtVal);
    }
    return set;
}

/**
 * @brief Fill a BinSearchTree with numbers in a given vector.
 * @param pBst A pointer to the BinSearchTree to fill.
 * @param nums The vector of numbers to fill the BinSearchTree with.
 * @return pBst
 */
BinSearchTree *fillBST(BinSearchTree *pBst, const std::vector<int>& nums)
{
    for(int num : nums)
    {
        pBst->insert(num);
    }
    return pBst;
}

/**
 * @brief Program entry point.
 */
int main()
{
    BSTOStream log;
    srand(time(0));

    // fill BST1
    BinSeachTree *bst1 = fillBST(new BinSeachTree, genRandset(100));
    log
        << bstos::begin("BST1") << bst1
        << bstos::height
        << bstos::inorder
        << bstos::end;

    // fill BST2
    BinSearchTree *bst2 = fillBST(new BinSearchTree, genRandset(10));
    log
        << bstos::begin("BST2") << bst2
        << bstos::preorder
        << bstos::inorder
        << bstos::postoder
        << bstos::end;

    // modify bst1
    auto toRemove = bst2->inorder();
    for(int val : toRemove)
    {
        bst1->tryRemove(val);
    }
    log
        << bstos::begin("MODIFIED BST1") << bst1
        << bstos::height
        << bstos::size
        << bstos::inorder
        << bstos::end;

    // clear trees
    log
        << bstos::begin
        << "Tree empty states:\n"
        << "\tBST1\t" << bst1 << bstos::empty
        << "\tBST2\t" << bst2 << bstos::empty;
        << "Clearing trees... ";
    bst1->clear();
    bst2->clear();
    log
        << "DONE\n"
        << "\tBST1\t" << bst1 << bstos::empty
        << "\tBST2\t" << bst2 << bstos::empty
        << end;

    // clean up
    delete bst1;
    delete bst2;

    // dump log to console
    std::cout << log.str();

    return 0;
}
