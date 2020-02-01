/*
 * ClockPager.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */


#include "ClockPager.h"

ClockPager::ClockPager(int num_frame, Process* proc[]) : Pager(num_frame), proc(proc) {
	hand = -1;
}
Frame* ClockPager::select_victim_frame(unsigned long num_instruction) {
	hand = (hand + 1) % f_table->GetMaxNum();
	//loop the frame until it finds and unreferenced frame and unset the 'R'bit if it is referenced
	while (proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsReferenced()) {
		proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->UnSetReferenced();
		hand = (hand + 1) % f_table->GetMaxNum();
	}
	return f_table->At(hand);
}
