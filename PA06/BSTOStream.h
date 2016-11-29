/**
 * @file
 * @brief Header file for the BST ostream interface.
 * @author Matthew Bauer
 */
#ifndef BST_OSTREAM_H
#define BST_OSTREAM_H

#include <sstream>
#include <string>
#include "BinSearchTree.h"

namespace bstos
{
    /**
     * @brief Tellthe BSTOStream to begin a section.
     * @details Holds the the name that BSTOStream uses to title the section.
     */
    struct begin
    {
    public:
        std::string name;

        /**
         * @brief Construct a begin token with the given name.
         * @param name The name of the section.
         */
        begin(const std::string& name);

        /**
         * @brief Construct a begin token with no (aka a blank) name.
         */
        begin();
    };

    /**
     * @brief Generic structure to hold tokens to feed BSTOStream.
     */
    struct token
    {
    public:
        int id;

        /**
         * @brief Construct a token with the given ID.
         * @details For internal use only.
         */
        token(int id);

        /**
         * @brief Test for equality between two tokens.
         * @param other The token to compare this one to.
         * @return Whether the tokens are equal.
         */
        bool operator==(const token& other);
    };

    /**
     * @brief Tell the BSTOStream to print out the BST height.
     */
    const token height(0);

    /**
     * @brief Tell the BSTOStream to print out the BST size.
     */
    const token size(1);

    /**
     * @brief Tell the BSTOStream to print out the BST contents in PREORDER.
     */
    const token preorder(2);

    /**
     * @brief Tell the BSTOStream to print out the BST contents in INORDER.
     */
    const token inorder(3);

    /**
     * @brief Tell the BSTOStream to print out the BST contents in POSTORDER.
     */
    const token postorder(4);

    /**
     * @brief Tell the BSTOStream to end a section.
     */
    const token end(5);
};

class BSTOStream : public std::ostringstream
{
private:
    BinSearchTree *currBST;

public:
    /**
     * @brief Construct an empty BSTOStream.
     */
    BSTOStream();

    /**
     * @brief Set the current BST.
     * @param bst The new BST to use.
     * @return A reference to this stream.
     */
    BSTOStream& operator<<(const BinSearchTree*& bst);

    /**
     * @brief Start a section.
     * @param bgn The begin token to use.
     * @return A reference to this stream.
     */
    BSTOStream& operator<<(const bstos::begin& bgn);

    /**
     * @brief Handle a token.
     * @param tkn The token to handle.
     * @pre tkn is a valid token (as defined in the bstos namespace).
     * @return A reference to this stream.
     */
     BSTOStream& operator<<(const bstos::token& tkn);
};

#endif
