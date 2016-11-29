/**
 * @file
 * @brief Implementation file for the BSTOS interface.
 * @author Matthew Bauer
 */

#include "BSTOStream.h"
#include <vector>

const std::string HBAR_SEP = "----------";

// helper func
/**
 * @brief Print the values in an integer vector to an ostringstream.
 * @details Format: "val1, val2, val3, valX..."
 * @param vec The vector to print.
 * @param oss A pointer to the ostringstream to send vector contents to.
 */
void ossTakeVec(const std::vector<int>& vec, std::ostringstream *oss)
{
    for(int iter = 0; iter < vec.size(); iter++)
    {
        (*oss) << vec[iter];
        if(iter != vec.size()-1)
        {
            (*oss) << ", ";
        }
    }
}

// bstos defines
bstos::begin::begin(const std::string& name)
{
    this->name = name;
}

bstos::begin::begin()
{
    name = "";
}

bstos::token::token(int id)
{
    this->id = id;
}
bool bstos::token::operator==(const bstos::token& other) const
{
    return (id == other.id);
}


// BSTOStream defines
BSTOStream::BSTOStream() : std::ostringstream()
{
    currBST = nullptr;
    nameLen = 0;
}

BSTOStream& BSTOStream::operator<<(BinSearchTree* bst)
{
    currBST = bst;
    return *this;
}

BSTOStream& BSTOStream::operator<<(const bstos::begin& bgn)
{
    *this << HBAR_SEP << bgn.name << HBAR_SEP << "\n";
    nameLen = bgn.name.size();
    return *this;
}

BSTOStream& BSTOStream::operator<<(const bstos::token& tkn)
{
    if(tkn == bstos::end)
    {
        *this << HBAR_SEP << HBAR_SEP;
        for(int iter = 0; iter < nameLen; iter++)
        {
            *this << "-";
        }
        *this << "\n\n";
    }
    else if(currBST)
    {
        if(tkn == bstos::height)
        {
            *this << "Height: " << currBST->height() << "\n";
        }
        else if(tkn == bstos::size)
        {
            *this << "# of nodes: " << currBST->size() << "\n";
        }
        else if(tkn == bstos::empty)
        {
            *this
                << "Empty: " << (currBST->isEmpty() ? "TRUE" : "FALSE")
                << "\n";
        }
        else if(tkn == bstos::preorder)
        {
            *this << "Data in PREORDER:\n";
            ossTakeVec(currBST->preorder(), (std::ostringstream*)this);
            *this << "\n";
        }
        else if(tkn == bstos::inorder)
        {
            *this << "Data in INORDER:\n";
            ossTakeVec(currBST->inorder(), (std::ostringstream*)this);
            *this << "\n";
        }
        else if(tkn == bstos::postorder)
        {
            *this << "Data in POSTORDER:\n";
            ossTakeVec(currBST->postorder(), (std::ostringstream*)this);
            *this << "\n";
        }
        else
        {
            // invalid token. don't do anything now, but know that it makes
            //     the whole world sad when this happens.
        }
    }
    return *this; // fails silently if !=end && !currBST (TODO change?)
}
