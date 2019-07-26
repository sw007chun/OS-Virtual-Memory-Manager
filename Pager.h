/*
 * Pager.h
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#ifndef PAGER_H_
#define PAGER_H_

#include <iostream>
#include <queue>
#include <iomanip>
#include "FrameTable.h"
#include "PageTableEntry.h"
using namespace std;

extern int doAging;
//#define traceAge(fmt...) do { if (doAging > 0) { cout << "ASELECT " << fmt << endl; fflush(stdout); } } while (0)

class Pager{
protected:
	FrameTable* f_table;
public:
	Pager (int num_frame);
	Frame* GetFrame(int num_instruction);
	virtual Frame* select_victim_frame(unsigned long num_instruction) = 0;
	virtual ~Pager();
	void PrintFrameTable();
	void SetFree(int v_page_num);
};

#endif /* PAGER_H_ */
