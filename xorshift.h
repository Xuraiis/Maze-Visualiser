/*
 * XOrShift.h
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#ifndef XORSHIFT_H_
#define XORSHIFT_H_

 #include <ctime>

class XOrShift {
protected:
	unsigned long reg;

public:
	XOrShift();
	XOrShift(long seed);
	virtual ~XOrShift();
	long rand();
	long rand_to(long);
	long rand_from_to(long, long);
};

#endif /* XORSHIFT_H_ */
