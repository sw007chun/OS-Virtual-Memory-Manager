/*
 * FIFOPager.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#ifndef FIFOPAGER_CPP_
#define FIFOPAGER_CPP_

#include "FIFOPager.h"

//FIFOPager::FIFOPager(FrameTable* frame_table) : Pager(frame_table) {
////	cout << fifo_q.empty() << endl;
//}

FIFOPager::FIFOPager(int num_frame) : Pager(num_frame) {
	counter = -1;
}

Frame* FIFOPager::select_victim_frame() {
	counter = (counter + 1) % f_table->GetMaxNum();
	return f_table->At(counter);
//	if (!fifo_q.empty()) {
//		PTE * p = fifo_q.front();
//		fifo_q.pop();
//
////		cout << "pop: " << p->p_frame << endl;
//		return f_table->At(p->GetPageFrame());
//	} else
//		return NULL;
}
void FIFOPager::add_page(PTE *page_entry) {
//	fifo_q.push(page_entry);
//	cout << "add: " << page_entry->p_frame << endl;
}

#endif /* FIFOPAGER_CPP_ */
