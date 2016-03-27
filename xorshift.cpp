/*
 * XOrShift.cpp
 *
 *  Created on: 24 Mar 2016
 *      Author: Nathan
 */

#include "xorshift.h"

XOrShift::XOrShift() {
	reg = time(0);
}

XOrShift::XOrShift(long seed) {
	reg = seed;
}

XOrShift::~XOrShift() {}

long XOrShift::rand() {
	reg ^= (reg << 21);
	reg ^= (reg >> 35);
	reg ^= (reg << 4);
	return reg >> 1;
}

long XOrShift::rand_from_to(long a, long b) {
	return a + rand() % (b - a);
}

long XOrShift::rand_to(long b) {
	return rand() % b;
}
