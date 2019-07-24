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
#include "FrameTable.h"
#include "PageTableEntry.h"
using namespace std;

class Pager{
protected:
	FrameTable* f_table;
public:
//	Pager (FrameTable* frame_table);
	Pager (int num_frame);
	Frame* GetFrame();
	void PrintFrameTable();
	virtual Frame* select_victim_frame() = 0;
	virtual void add_page(PTE *page_enty) = 0;
	virtual ~Pager() { };
	void SetFree(int v_page_num);
	void SetReferenced(int frame_num);
};

#endif /* PAGER_H_ */
