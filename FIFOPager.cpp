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
	counter = -1;
}

Frame* FIFOPager::select_victim_frame(int num_instruction) {
	counter = (counter + 1) % f_table->GetMaxNum();
	return f_table->At(counter);
}

#endif /* FIFOPAGER_CPP_ */
