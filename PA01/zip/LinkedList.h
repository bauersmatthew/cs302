/**
 * @file LinkedList.h
 * @brief Interface file for the LinkedList data type
 * @author Matthew Bauer
 * @details Specifies the interface of the LinkedList data type
 * @Note Adapted from/inspired by "Data Abstractions & Problem Solving
 * 	with C++" Seventh Edition by Frank M. Carrano and Timothy M.
 * 	Henry.
 */

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "ListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
	Node<ItemType> *head;
	int numItems;

public:
	/**
	 * @brief Constructs an empty linked list.
	 */
	LinkedList();
	
	/**
	 * @brief Copies the contents of another linked list.
	 * @param other The linked list to copy.
	 */
	LinkedList(const LinkedList<ItemType>& other);
	
	/**
	 * @brief Destructs the linked list object.
	 */
	virtual ~LinkedList();

	/**
	 * @brief Sees whether this list is empty.
	 * @return True if the list is empty, false othersise.
	 */
	bool isEmpty() const;
	
	/*
	 * @brief Gets the length of the list.
	 * @return The length of the list.
	 */
	int getLength() const;
	
	/*
	 * @brief Inserts an entry into the list at the given position.
	 * @pre 1 <= newPosition <= getLength() + 1
	 * @post newEntry will be in the list at the location described
	 * 	by newLocation, and any entries after it will be
	 * 	shifted accordingly.
	 * @param newPosition The position to insert newEntry at.
	 * @param newEntry The entry to insert.
	 * @return True on insertion success, false on failure.
	 */
	bool insert(int newPosition, const ItemType& newEntry);
	
	/*
	 * @brief Removes the entry at the given position from the list.
	 * @pre getLength() != 0, 1 <= position <= getLength()
	 * @post The item that was found at the given position will no
	 * 	longer be contained in the list. The locations of any
	 * 	entries after the removed entry will be adjusted
	 * 	accordingly.
	 * @param position The position of the entry to remove.
	 * @return True on removal success, false on failure.
	 */
	bool remove(int position);
	
	/*
	 * @brief Removes all entries from the list.
	 * @post The list will be empty.
	 */
	void clear();
	
	/**
	 * @brief Gets the entry found at the given position.
	 * @details Throws PrecondViolatedExcept on precondition
	 * 	violation.
	 * @pre getLength() != 0, 1 <= position <= getLength()
	 * @param position The position of the entry to return.
	 * @return The entry at the specified position.
	 */
	ItemType getEntry(int position) const throw(PrecondViolatedExcept);
	
	/**
	 * @brief Replaces the entry at the given position with the
	 * 	specified new entry.
	 * @details Throws PrecondViolatedExcept on precondition
	 * 	violation.
	 * @pre getLength() != 0, 1 <= position <= getLength()
	 * @post The entry at the given position has been replaced.
	 * @param position The position of the entry to replace.
	 * @param newEntry The new value of the entry.
	 */
	void replace(int position, const ItemType& newEntry)
		throw(PrecondViolatedExcept);
};

#include "LinkedList.cpp"
#endif
