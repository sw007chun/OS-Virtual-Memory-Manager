/*
 * FIFOPager.h
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#ifndef FIFOPAGER_H_
#define FIFOPAGER_H_

#include "Pager.h"

class FIFOPager : public Pager {
private:
	int counter;
public:
	FIFOPager(int num_frame);
	Frame* select_victim_frame(unsigned long num_instruction);
	~FIFOPager() { };
};

#endif /* FIFOPAGER_H_ */
