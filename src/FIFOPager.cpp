/*
 * FIFOPager.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#ifndef FIFOPAGER_CPP_
#define FIFOPAGER_CPP_

#include "FIFOPager.h"

FIFOPager::FIFOPager(int num_frame) : Pager(num_frame) {
	hand = -1;
}
Frame* FIFOPager::select_victim_frame(unsigned long num_instruction) {
	hand = (hand + 1) % f_table->GetMaxNum();
	if (doAging)
		cout << "ASELECT " << hand << endl;
	return f_table->At(hand);
}

#endif /* FIFOPAGER_CPP_ */
