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

void RBTree::insert(int value)
{
    if(isEmpty())
    {
        // insert as the head node (black)
        head = new RBTNode(value, nullptr, RBTColor::BLACK);
        return;
    }
    // else

    // insert into tree like a normal binary
    RBTNode *loc = head;
    RBTNode **locLoc = &head;
    RBTNode *last = nullptr;
    while(loc)
    {
        if(value < loc->value)
        {
            last = loc;
            loc = loc->left;
            locLoc = &loc->left;
        }
        else
        {
            last = loc;
            loc = loc->right;
            locLoc = &loc->right;
        }
    }
    // location found; construct new red node at that spot
    *locLoc = new RBTNode(value, last);


    if(loc->parent->color == RBTColor::BLACK)
    {
        // wikipedia case 2; nothing else to do
        return;
    }
    // else

    RBTNode *grandparent = loc->getGrandparent();
    RBTNode *uncle = loc->getUncle();

    if(uncle && uncle->color == RBTColor::RED)
    {
        // wikipedia case 3;
        loc->parent->color = RBTColor::BLACK;
        uncle->color = RBTColor::BLACK;
        grandparent->color = RBTColor::RED;
        loc->color = RBTColor::BLACK;
        return;
    }
    // else

    if(loc == loc->parent->right && loc->parent == grandparent->left)
    {
        // wikipedia case 4 (part 1);
        rotateLeft(loc->parent);
        loc = loc->left;
        // NO RETURN; CONTINUE TO CASE 5
    }
    else if(loc == loc->parent->left && loc->parent == grandparent->right)
    {
        // wikipedia case 4 (part 2);
        rotateRight(loc->parent);
        loc = loc->right;
        // NO RETURN; CONTINUE TO CASE 5
    }

    loc->parent->color = RBTColor::BLACK;
    grandparent->color = RBTColor::RED;
    if(loc == loc->parent->left)
    {
        rotateRight(grandparent);
    }
    else
    {
        rotateLeft(grandparent);
    }

    // ok hopefully done now...
}
