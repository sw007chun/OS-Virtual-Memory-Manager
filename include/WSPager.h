/*
 * WSPager.h
 *
 *  Created on: Jul 25, 2019
 *      Author: sungw
 */

#ifndef WSPAGER_H_
#define WSPAGER_H_


#include "Pager.h"
#include "Process.h"

class WSPager : public Pager {
private:
	static const int TAU = 49;
	int hand;
	Process** proc;
public:
	WSPager(int num_frame, Process** proc);
	Frame* select_victim_frame(unsigned long num_instruction);
	~WSPager() { };
};


#endif /* WSPAGER_H_ */
