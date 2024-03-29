/**
 * @file
 * @brief Header file for the binary search tree interface.
 * @author Matthew Bauer
 */
#ifndef BIN_SEARCH_TREE_H
#define BIN_SEARCH_TREE_H

#include <vector>

/**
 * @brief Represents a Binary Search Tree.
 */
class BinSearchTree
{
private:
    /**
     * @brief The value of this node.
     */
    int root;
    
    /**
     * @brief Whether or this node is not empty.
     * @details Should only ever be false when the top-level tree is empty.
     */
    bool hasRoot;
    
    /**
     * @brief Points to the left branch coming off this node.
     */
    BinSearchTree *left;
    
    /**
     * @brief Points to the right branch coming off this node.
     */
    BinSearchTree *right;

    /**
     * @brief The parent node's pointer to this tree.
     * @details Is nullptr when there is no parent node ==> this is the highest
     *     node.
     */
    BinSearchTree **parentThis;

    /**
     * @brief Get the rightmost node in the tree.
     * @details For internal use.
     * @return The rightmost node in the tree.
     */
    BinSearchTree *getRightmostNode();

    /**
     * @brief Construct a sub-BinSearchTree (==> has a parent tree).
     * @details For internal use.
     * @param val The root value to use.
     * @param prnt The parent tree's pointer to this tree.
     */
    BinSearchTree(int val, BinSearchTree **prntThs);

public:

    /**
     * @brief Construct an empty binary search tree.
     */
    BinSearchTree();

    /**
     * @brief Construct a binary search tree with given root value.
     * @param val The root value to use.
     */
    explicit BinSearchTree(int val);

     /**
      * @brief Destructs the tree.
      */
    ~BinSearchTree();

    /**
     * @brief Insert a value into the tree.
     * @details If the value is already present in the tree, do nothing.
     * @param val The value to insert.
     */
    void insert(int val);

    /**
     * @brief Try to remove a value.
     * @details If the value is present in the tree, remove it. If the value
     *     is not present, do nothing.
     * @param val The value to attempt removal of.
     * @return Whether a value was removed.
     */
    bool tryRemove(int val);

    /**
     * @brief Clear the tree of all values.
     */
    void clear();

    /**
     * @brief Get the height of the tree.
     * @return The height of the tree.
     */
     int height() const;

     /**
      * @brief Get the size of the tree.
      * @return The size of the tree.
      */
     int size() const;

     /**
      * @brief Get whether the tree is empty.
      * @return Whether the tree is empty.
      */
     bool isEmpty() const;

     /**
      * @brief Get a vector containing the tree values in PREORDER.
      * @return A vector containing the tree values in PREORDER.
      */
     std::vector<int> preorder() const;

     /**
      * @brief Get a vector containing the tree values in INORDER.
      * @return A vector containing the tree values in INORDER.
      */
     std::vector<int> inorder() const;

     /**
      * @brief Get a vector containing the tree values in POSTORDER.
      * @return A vector containing the tree values in POSTORDER.
      */
     std::vector<int> postorder() const;
};

#endif
