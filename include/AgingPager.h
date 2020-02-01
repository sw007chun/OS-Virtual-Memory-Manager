/*
 * AgingPager.h
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#ifndef AGINGPAGER_H_
#define AGINGPAGER_H_


#include "Pager.h"
#include "Process.h"

class AgingPager : public Pager {
private:
	int hand;
	Process** proc;
public:
	AgingPager(int num_frame, Process** proc);
	Frame* select_victim_frame(unsigned long num_instruction);
	~AgingPager() { };
};



#endif /* AGINGPAGER_H_ */
