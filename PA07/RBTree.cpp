/**
 * @file
 * @brief Implementation file for the RBTree interface.
 * @author Matthew Bauer
 */

#include "RBTree.h"voidvoid

#define MAX(a, b) (a>b?a:b)

// RBTNODE DEFS
RBTNode::RBTNode(int value, RBTNode *parent, RBTColor color)
{
    this->value = value;
    this->parent = parent;
    this->color = color;

    this->left = this->right = nullptr;
}

RBTNode *RBTNode::getGrandparent()
{
    if(!parent)
    {
        return nullptr;
    }
    return parent->parent;
}
RBTNode *RBTNode::getUncle()
{
    RBTNode *gp = getGrandparent();
    if(!gp)
    {
        return nullptr;
    }
    if(parent == gp->left)
    {
        return gp->right;
    }
    else
    {
        return gp->left;
    }
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

void RBTree::rotateLeft(RBTNode *stHead)
{
    RBTNode *toDefer = stHead;
    RBTNode *newHead = stHead->right;
    RBTNode *highest = stHead->parent;

    highest->left = newHead;
    newHead->parent = highest;

    RBTNode *savedLeft = newHead->left;
    newHead->left = toDefer;
    toDefer->parent  = newHead;

    toDefer->right = savedLeft;
}
void RBTree::rotateRight(RBTNode *stHead)
{
    RBTNode *toDefer = stHead;
    RBTNode *newHead = stHead->left;
    RBTNode *highest = stHead->parent;

    highest->right = newHead;
    newHead->parent = highest;

    RBTNode *savedRight = newHead->right;
    newHead->right = toDefer;
    toDefer->parent = newHead;

    toDefer->left = savedRight;
}

int RBTree::getSubtreeHeight(RBTNode *stHead)
{
    int maxH = 0;
    if(stHead->left)
    {
        maxH = MAX(maxH, getSubtreeHeight(stHead->left)+1);
    }
    if(stHead->right)
    {
        maxH = MAX(maxH, getSubtreeHeight(stHead->right)+1);
    }
    return maxH;
}

int RBTree::getSubtreeSum(RBTNode *stHead)
{
    int sum = stHead->value;
    if(stHead->left)
    {
        sum += getSubtreeSum(stHead->left);
    }
    if(stHead->right)
    {
        sum += getSubtreeSum(stHead->right);
    }
    return sum;
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

void RBTree::clear()
{
    if(head)
    {
        delete head;
    }
    head = nullptr;
}

bool RBTree::isEmpty()
{
    return !head;
}

int RBTree::getHeight()
{
    if(!head)
    {
        return -1;
    }
    return getSubtreeHeight(head);
}

int RBTree::sum()
{
    if(!head)
    {
        return 0;
    }
    return getSubtreeSum(head);
}
