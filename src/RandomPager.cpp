/*
 * RandomPager.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#include "RandomPager.h"

RandomPager::RandomPager(int num_frame, int *rand, int rlength) : Pager(num_frame), rand(rand), rlength(rlength) {
	rofs = -1;
}

Frame* RandomPager::select_victim_frame(unsigned long num_instruction) {
	rofs = (rofs + 1) % rlength;
	return f_table->At(rand[rofs] % f_table->GetMaxNum());
}
