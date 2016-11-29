#include "BinSearchTree.h"

// constructor/destructor defs
BinSearchTree::BinSearchTree()
{
    root = 0;
    hasRoot = false;
    left = right = nullptr;
}

BinSearchTree::BinSearchTree(int val)
{
    root = val;
    hasRoot = true;
    left = right = nullptr;
}

BinSearchTree::~BinSearchTree()
{
    clear();
}
