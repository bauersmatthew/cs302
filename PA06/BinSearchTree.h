/**
 * @file
 * @brief Header file for the binary search tree interface.
 * @author Matthew Bauer
 */
#ifndef BIN_SEARCH_TREE_H
#define BIN_SEARCH_TREE_H

#include <vector>

class BinSearchTree
{
private:
    int root;
    bool hasRoot;
    BinSearchTree *left;
    BinSearchTree *right;

public:

    /**
     * @brief Construct an empty binary search tree.
     */
    BinSearchTree();

    /**
     * @brief Construct a binary search tree with given root value.
     * @param val The root value to use.
     */
     BinSearchTree(int val);

     /**
      * @brief Destructs the tree.
      */
    ~BinSearchTree();

    /**
     * @brief Insert a value into the tree.
     * @param val The value to insert.
     */
    void insert(int val);

    /*
     * @brief Try to remove a value.
     * @details If the value is present in the tree, remove the first instance
     *     found. If the value is not present, do nothing.
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
     int height();

     /**
      * @brief Get the size of the tree.
      * @return The size of the tree.
      */
     int size();

     /**
      * @brief Get whether the tree is empty.
      * @return Whether the tree is empty.
      */
     bool isEmpty();

     /**
      * @brief Get a vector containing the tree values in PREORDER.
      * @return A vector containing the tree values in PREORDER.
      */
     std::vector<int> preorder();

     /**
      * @brief Get a vector containing the tree values in INORDER.
      * @return A vector containing the tree values in INORDER.
      */
     std::vector<int> inorder();

     /**
      * @brief Get a vector containing the tree values in POSTORDER.
      * @return A vector containing the tree values in POSTORDER.
      */
     std::vector<int> postorder();
};

#endif
