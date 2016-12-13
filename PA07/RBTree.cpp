/**
 * @file
 * @brief Implementation file for the RBTree interface.
 * @author Matthew Bauer
 */

#include "RBTree.h"

// RBTNODE DEFS
RBTNode::RBTNode(int value, RBTNode *parent, RBTColor color)
{
    this->value = value;
    this->parent = parent;
    this->color = color;

    this->left = this->right = nullptr;
}

// RBTREE DEFS
RBTree::RBTree()
{
    head = nullptr;
}
RBTree::~RBTree()
{
    clear();
}
