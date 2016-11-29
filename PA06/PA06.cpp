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
 * @brief Generate a set of random integers 1-200 with given length.
 * @param num The length of the set to generate.
 * @return The generated set.
 */
std::vector<int> genRandset(int num)
{
    std::vector<int> set;
    while(num--)
    {
        set.push_back((rand()%200)+1)
    }
    return set;
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
}
