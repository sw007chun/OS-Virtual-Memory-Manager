/*
 * RandomPager.h
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#ifndef RANDOMPAGER_H_
#define RANDOMPAGER_H_

#include "Pager.h"
#include "FrameTable.h"

class RandomPager : public Pager {
private:
	int rofs;
	int *rand;
	int rlength;
public:
	RandomPager(int num_frame, int *rand, int rlength);
	Frame* select_victim_frame(unsigned long num_instruction);
	~RandomPager() { };
};

#endif /* RANDOMPAGER_H_ */
