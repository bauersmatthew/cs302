#include "BinSearchTree.h"

// convenience funcs
/**
 * @brief Add two vectors together.
 * @param vec1 The first vector.
 * @param vec2 The second vector.
 * @return A vector containing the values of vec1 and vec2 (in that order).
 */
std::vector<int> addVecs(const std::vector<int>& vec1, const std::vector<int>& vec2)
{
    std::vector<int> newVec;
    for(int val : vec1)
    {
        newVec.push_back(val);
    }
    for(int val : vec2)
    {
        newVec.push_back(val);
    }
    return newVec;
}
/**
 * @brief Add one vector's contents onto the end of another.
 * @param vec1 The destination vector (to be modified).
 * @param vec2 The source vector.
 */
void addToVec(std::vector<int>& vec1, const std::vector<int>& vec2)
{
    vec1 = addVecs(vec1, vec2);
}

// constructor/destructor defs
BinSearchTree::BinSearchTree()
{
    root = 0;
    hasRoot = false;
    left = right = nullptr;
    parentThis = nullptr;
}

BinSearchTree::BinSearchTree(int val)
{
    root = val;
    hasRoot = true;
    left = right = nullptr;
    parentThis = nullptr;
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

// random support funcs
BinSearchTree *BinSearchTree::getRightmostNode()
{
    if(right)
    {
        return right->getRightmostNode();
    }
    else
    {
        return this;
    }
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
            else if((left && !right) || (!left && right))
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
                *(leftbr_rightmost->parentThis) = leftbr_rightmost->left;
                if(leftbr_rightmost->left)
                {
                    leftbr_rightmost->left->parentThis =
                        leftbr_rightmost->parentThis;
                }

                // destruct rightmost; all the data is saved
                leftbr_rightmost->left = nullptr;
                delete leftbr_rightmost;

                return true;
            }
        }
        else if(val > root)
        {
            if(right)
            {
                return right->tryRemove(val);
            }
            else
            {
                return false;
            }
        }
        else
        {
            // val < root
            if(left)
            {
                return left->tryRemove(val);
            }
            else
            {
                return false;
            }
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

// info functions
int BinSearchTree::height() const
{
    int leftHeight = left ? left->height()+1 : 0;
    int rightHeight = right ? right->height()+1 : 0;
    return (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int BinSearchTree::size() const
{
    if(!hasRoot)
    {
        return 0;
    }
    else
    {
        int leftSize = left ? left->size() : 0;
        int rightSize = right ? right->size() : 0;
        return (leftSize + rightSize + 1);
    }
}

bool BinSearchTree::isEmpty() const
{
    return !size();
}

// vec-out functions
std::vector<int> BinSearchTree::preorder() const
{
    std::vector<int> list;

    if(!hasRoot)
    {
        return list; // give back empty list b/c empty tree
    }
    else
    {
        list.push_back(root);
        if(left)
        {
            addToVec(list, left->preorder());
        }
        if(right)
        {
            addToVec(list, right->preorder());
        }
        return list;
    }
}

std::vector<int> BinSearchTree::inorder() const
{
    std::vector<int> list;

    if(!hasRoot)
    {
        return list;
    }
    else
    {
        if(left)
        {
            addToVec(list, left->inorder());
        }
        list.push_back(root);
        if(right)
        {
            addToVec(list, right->inorder());
        }
        return list;
    }
}

std::vector<int> BinSearchTree::postorder() const
{
    std::vector<int> list;

    if(!hasRoot)
    {
        return list;
    }
    else
    {
        if(left)
        {
            addToVec(list, left->postorder());
        }
        if(right)
        {
            addToVec(list, right->postorder());
        }
        list.push_back(root);
        return list;
    }
}
