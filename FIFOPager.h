/*
 * FIFOPager.h
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#ifndef FIFOPAGER_H_
#define FIFOPAGER_H_

#include "Pager.h"
#include "FrameTable.h"

class FIFOPager : public Pager {
private:
	queue <pte *> fifo_q;
public:
	FIFOPager(FrameTable* frame_table);
	Frame* select_victim_frame();
	void add_page(pte *page_enty);
	~FIFOPager() { };
};



#endif /* FIFOPAGER_H_ */
