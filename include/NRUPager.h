/*
 * NRUPager.h
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#ifndef NRUPAGER_H_
#define NRUPAGER_H_

#include "Pager.h"
#include "Process.h"

class NRUPager : public Pager {
private:
	unsigned long last_reset_time;
	static const int reset_interval = 50;
	int hand;
	Process** proc;
public:
	NRUPager(int num_frame, Process** proc);
	Frame* select_victim_frame(unsigned long num_instruction);
	~NRUPager() { };
};



#endif /* NRUPAGER_H_ */
