/*
 * SimpleList.cpp
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

 #include "intlist.h"

IntList::IntList(int arg_max_size) {
	max_size = arg_max_size;
	index = 0;
	array = new int[arg_max_size]{0};
}

IntList::~IntList() {
	delete[] array;
}

int IntList::size() {
	return index;
}

int IntList::size_max() {
	return max_size;
}

bool IntList::is_empty() {
	return size() < 1;
}

int IntList::add(int a) {
	return (array[index++] = a);
}

int IntList::get(int i) {
	return array[i];
}

int IntList::operator[](int i)  {
	return array[i];
}

int IntList::pop() {
	return array[--index];
}

int IntList::last() {
	return array[index-1];
}

int IntList::remove(int i) {
	int r = array[i];
	array[i] = array[--index];
	return r;
}

void IntList::clear() {
	index = 0;
}
