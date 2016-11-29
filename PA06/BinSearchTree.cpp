#include "BinSearchTree.h"

// constructor/destructor defs
BinSearchTree::BinSearchTree()
{
    root = 0;
    hasRoot = false;
    left = right = parentThis nullptr;
}

BinSearchTree::BinSearchTree(int val)
{
    root = val;
    hasRoot = true;
    left = right = parentThis = nullptr;
}

BinSearchTree::BinSearchTree(int val, BinSearchTree **prntThs)
{
    root = val;
    hasRoot = true;
    left = right = nullptr;
    parentThis = prntThs;
}

BinSearchTree::~BinSearchTree()
{
    clear();
}

// data manipulation defs
void BinSearchTree::insert(int val)
{
    if(!hasRoot)
    {
        root = val;
        hasRoot = true;
    }
    else
    {
        if(val > root)
        {
            if(right)
            {
                right->insert(val);
            }
            else
            {
                right = new BinSearchTree(val, &right);
            }
        }
        else if(val < root)
        {
            if(left)
            {
                left->insert(val);
            }
            else
            {
                left = new BinSearchTree(val, &left);
            }
        }
        else
        {
            // val already in tree; do nothing.
        }
    }
}

// this function is unbelievably ugly right now.
bool BinSearchTree::tryRemove(int val)
{
    if(!hasRoot)
    {
        return false;
    }
    else
    {
        if(val == root)
        {
            // remove self
            if(!left && !right)
            {
                // ==> case: no children
                // strategy: remove if not head tree; else mark as removed.
                if(parentThis)
                {
                    // actually remove
                    *parentThis = nullptr;
                    delete this;
                }
                else
                {
                    // just remove nominally
                    hasRoot = false;
                }

                return true;
            }
            else if((left && !right) || (!left && right)))
            {
                // ==> case: one child
                // strategy: absorb child
                BinSearchTree *oldChild = (left ? left : right);

                root = oldChild->root;
                hasRoot = oldChild->hasRoot;
                left = oldChild->left;
                right = oldChild->right;
                // DO NOT REPLACE PARENTTHIS!

                // destruct child silently
                oldChild->left = oldChild->right = nullptr;
                delete oldChild;

                return true;
            }
            else
            {
                // ==> case: two children
                // strategy: replace this node with the rightmost child of the
                //     left branch, replacing that node with its left child
                //     (if it exists).
                BinSearchTree *leftbr_rightmost = left->getRightmostNode();

                // replace self with rightmost node
                root = leftbr_rightmost->root;
                hasRoot = leftbr_rightmost->hasRoot;
                // DO NOT REPLACE LEFT, RIGHT, OR PARENTTHIS!

                // connect rightmost's left child with rightmost's parent.
                *(leftbr_rightmost->parentthis) = leftbr_rightmost->left;
                if(leftbr_rightmost->left)
                {
                    leftbr_rightmost->left->parentthis =
                        leftbr_rightmost->parentthis;
                }

                // destruct rightmost; all the data is saved
                leftbr_rightmost->left = nullptr;
                delete leftbr_rightmost;

                return true;
            }
        }
        else if(val > root)
        {
            return right->tryRemove(val);
        }
        else
        {
            // val < root
            return left->tryRemove(val);
        }
        // doesn't reach here
    }
    // or here
}

void BinSearchTree::clear()
{
    if(left)
    {
        delete left;
        left = nullptr;
    }
    if(right)
    {
        delete right;
        right = nullptr;
    }
    hasRoot = false;
}
