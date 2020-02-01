/*
 * ClockPager.h
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#ifndef CLOCKPAGER_H_
#define CLOCKPAGER_H_

#include "Pager.h"
#include "Process.h"

class ClockPager : public Pager {
private:
	int hand;
	Process** proc;
public:
	ClockPager(int num_frame, Process** proc);
	Frame* select_victim_frame(unsigned long num_instruction);
	~ClockPager() { };
};



#endif /* CLOCKPAGER_H_ */
