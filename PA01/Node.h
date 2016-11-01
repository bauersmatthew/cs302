/**
 * @file Node.h
 * @brief Interface file for the Node data type
 * @author Matthew Bauer
 * @details Specifies the interface of the Node data type
 * @Note Specification taken from "Data Abstractions a& Problem Solving
 * 	with C++" Seventh Edition by Frank Carrano and Timothy M.;
 * 	doxygen comments written by Matthew Bauer (student).
 */

#ifndef _NODE
#define _NODE

template<class ItemType>
class Node
{
private:
	ItemType item;
	Node<ItemType>* next;
public:
	/**
	 * @brief Construct an empty node.
	 */
	Node();
	
	/**
	 * @brief Construct a node containing the given item.
	 * @post The node will contain the given item.
	 * @param anItem The item to contain.
	 */
	Node(const ItemType& anItem);
	
	/**
	 * @brief Construct a node containing the given item and
	 * 	pointing to the given next node.
	 * @post The node will contain the given item and will point
	 * 	to the given next node.
	 * @param anItem The item to contain.
	 * @param nextNodePtr The pointer to the next node.
	 */
	Node(const ItemType& anItem, Node<ItemType> *nextNodePtr);
	
	/**
	 * @brief Set the contained item to the given item.
	 * @post The item will have been set to the given item.
	 * @param anItem The new item to be contained.
	 */
	void setItem(const ItemType& anItem);
	
	/**
	 * @brief Set the next node to the given node.
	 * @post This node will point to the given next node.
	 * @param nextNodePtr The pointer to the next node.
	 */
	void setNext(Node<ItemType>* nextNodePtr);
	
	/**
	 * @brief Get the item contained by this node.
	 * @return The item contained by this node.
	 */
	ItemType getItem() const;
	
	/*
	 * @brief Get the next node pointed to by this node.
	 * @return The node pointed to by this node.
	 */
	Node<ItemType> *getNext() const;
};

#include "Node.cpp"
#endif
