/**
 * @file
 * @brief Declare the Red/Black Tree (RBTree) interface.
 * @author Matthew Bauer
 */

#ifndef RBTREE_H
#define RBTREE_H

/**
 * @brief Red/black tree node colors (red or black)
 */
enum RBTColor
{
    RED,
    BLACK
};

/**
 * @brief Model a red/black tree node.
 */
class RBTNode
{
public:
    /**
     * @brief The node color.
     */
    RBTColor color;

    /**
     * @brief The node relatives.
     * @details All can be NULL, if the relative does not exist.
     */
    RBTNode *parent, *left, *right;

    /**
     * @brief The value held by this node.
     */
    int value;

    /**
     * @brief Construct an RBTNode with given value, parent, and color.
     * @param value The value to hold.
     * @param parent The parent of this node.
     * @param color The color of this node. DEFAULT: RED
     */
    RBTNode(int value, RBTNode *parent=nullptr, RBTColor color=RBTColor::RED);

    /**
     * @brief Destruct the node.
     * @details Destructs all child nodes.
     */
    ~RBTNode();

    /**
     * @brief Get the grandparent of this node.
     * @return The grandparent of this node.
     */
    RBTNode *getGrandparent();

    /**
     * @brief Get the uncle of this node.
     * @return The uncle of this node.
     */
    RBTNode *getUncle();
};

/**
 * @brief Model a red/black tree.
 */
class RBTree
{
    /**
     * @brief The head (origin) node of the tree.
     * @details Is NULL if tree is empty.
     */
    RBTNode *head;

    /**
     * @brief Rotate the given subtree left.
     * @param stHead A pointer to the subtree's head node
     */
    void rotateLeft(RBTNode *stHead);

    /**
     * @brief Rotate the given subtree right.
     * @param stHead A pointer to the subtree's head node
     */
    void rotateRight(RBTNode *stHead);

public:
    /**
     * @brief Construct an empty RBTree.
     */
    RBTree();

    /**
     * @brief Destruct the tree, freeing all memory.
     */
    ~RBTree();

    /**
     * @brief Insert a value into the tree.
     */
     void insert(int value);

     /**
      * @brief Clear the tree.
      */
     void clear();

     /**
      * @brief Whether the tree is empty.
      * @return true if empty; false otherwise.
      */
     bool isEmpty();

     /**
      * @brief Get the height of the tree.
      * @return The height of the tree.
      */
     int getHeight();

     /**
      * @brief Compute the sum of all values in the tree.
      * @return The sum of all values in the tree.
      */
     int sum();
};

#endif
