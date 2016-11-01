/*
 * File: PA01.cpp
 * Edited: 18 Sep 2016
 * Author: Matthew Bauer
 */

#include "LinkedList.h"
#include <iostream>

#define TSTMSG(val) std::cout << val << std::endl
#define TM TSTMSG

int main()
{
	LinkedList<int> list;
	TM(list.isEmpty());
	TM(list.getLength());
	TM(list.insert(1, 100));
	TM(list.isEmpty());
	TM(list.getLength());
	TM(list.getEntry(1));
	TM(list.insert(2, 200));
	TM(list.getEntry(2));
	TM(list.remove(2));
	TM(list.getLength());
	TM(list.getEntry(1));
	TM(list.insert(2, 300));
	TM(list.insert(3, 400));
	TM(list.insert(4, 500));
	TM(list.getEntry(3));
	TM(list.remove(3));
	TM(list.remove(1));
	TM(list.getLength());
	TM(list.getEntry(2));
	TM(list.insert(2, 800));
	TM(list.getEntry(2));
	TM(list.getEntry(3));
	list.replace(2, 10600);
	TM(list.getEntry(2));
	list.clear();
	TM(list.isEmpty());
	
	return 0;
}
