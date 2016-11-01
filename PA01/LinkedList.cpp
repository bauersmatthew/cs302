/**
 * @file LinkedList.cpp
 * @brief Implementation file for the LinkedList data type
 * @author Matthew Bauer
 * @details Implements the LinkedList data type
 * @Note Adapted from/inspired by "Data Abstractions & Problem Solving
 * 	with C++" Seventh Edition by Frank M. Carrano and Timothy M.
 * 	Henry.
 */

#include "LinkedList.h"

template<class ItemType>
LinkedList<ItemType>::LinkedList()
{
	head = nullptr;
	numItems = 0;
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& other)
{
	for(int currItem = 1; currItem <= other.getLength(); currItem++)
	{
		insert(currItem, other.getEntry(currItem));
	}
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return (getLength() == 0);
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return numItems;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	// check preconditions
	if(newPosition < 1 || newPosition > getLength()+1)
	{
		return false;
	}
	
	// if list empty, do shortcut
	if(!head)
	{
		head = new Node<ItemType>(newEntry);
		numItems++;
		return true;
	}
	
	// get node to link to
	Node<ItemType> *preInsert = head;
	for(int posIter = 1; posIter < newPosition-1; posIter++)
	{
		preInsert = preInsert->getNext();
	}
	
	// save node after insert
	Node<ItemType> *postInsert = preInsert->getNext();
	
	// construct new node in place
	preInsert->setNext(new Node<ItemType>(newEntry, postInsert));
	
	// update entry count, return
	numItems++;
	return true;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	// check preconditions
	if(isEmpty() || position < 1 || position > getLength())
	{
		return false;
	}
	
	// find the node to remove and the one before it 
	Node<ItemType> *toRemove = head;
	Node<ItemType> *preRemove = nullptr;
	for(int posIter = 1; posIter < position; posIter++)
	{
		toRemove = toRemove->getNext();
		if(!preRemove)
		{
			preRemove = head;
		}
		else
		{
			preRemove = preRemove->getNext();
		}
	}
	
	// save node after removal
	Node<ItemType> *postRemove = toRemove->getNext();
	
	// delete target node
	delete toRemove;
	
	// link preRemove and postRemove
	if(preRemove)
	{
		// toRemove was not head
		preRemove->setNext(postRemove);
	}
	else
	{
		// toRemove was head
		head = postRemove;
	}
	
	// update entry count, return
	numItems--;
	return true;
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	// remove first element until empty
	while(!isEmpty())
	{
		remove(1);
	}
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
	throw(PrecondViolatedExcept)
{
	// check preconds
	if(isEmpty() || position < 1 || position > getLength())
	{
		throw PrecondViolatedExcept("invalid position");
	}
	
	// find, return
	Node<ItemType> *currNode = head;
	for(int nodeIter = 1; nodeIter < position; nodeIter++)
	{
		currNode = currNode->getNext();
	}
	return currNode->getItem();
}

template<class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry)
	throw(PrecondViolatedExcept)
{
	// check preconds
	if(isEmpty() || position < 1 || position > getLength())
	{
		throw PrecondViolatedExcept("invalid position");
	}
	
	// find, replace
	Node<ItemType> *currNode = head;
	for(int nodeIter = 1; nodeIter < position; nodeIter++)
	{
		currNode = currNode->getNext();
	}
	currNode->setItem(newEntry);
}
