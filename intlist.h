/*
 * SimpleList.h
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#ifndef INTLIST_H_
#define INTLIST_H_

class IntList {

protected:
	int max_size;
    int index;
    int *array;

public:
	IntList(int);
	virtual ~IntList();

    int size();
    int size_max();
    bool is_empty();

    int add(int a);
    int get(int index);
	int operator[](int index);
    int pop();
    int last();
    int remove(int index);

    void clear();
};

#endif /* INTLIST_H_ */

