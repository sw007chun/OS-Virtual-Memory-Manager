/*
 * NRUPager.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#include "NRUPager.h"

NRUPager::NRUPager(int num_frame, Process* proc[]) : Pager(num_frame), proc(proc) {
	hand = -1;
	last_reset_time = 0;
}

Frame* NRUPager::select_victim_frame(unsigned long num_instruction) {
	int frame_size = f_table->GetMaxNum();
	hand = (hand + 1) % frame_size;
	int class_num = proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsReferenced() * 2
			+ proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsModified();
	int min_class = class_num;
	int min_class_frame = hand;
	int i = 0;
	if (doAging)
		cout << "ASELECT: hand=" << setw(2) << hand << ' ' ;

	//loop until finds class 0 frame or find minimum class and its frame number
	while (++i < frame_size && class_num != 0) {
		hand = (hand + 1) % frame_size;
		class_num = proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsReferenced() * 2
				+ proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsModified();
		if (class_num < min_class) {
			min_class = class_num;
			min_class_frame = hand;
		}
	}
	hand = min_class_frame;
	//check if it is time to reset the counter
	if (num_instruction - last_reset_time >= reset_interval) {
		i = -1;
		last_reset_time = num_instruction;
		while (++i < frame_size) {
			proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->UnSetReferenced();
			hand = (hand + 1) % frame_size;
		}
	}
	if (doAging)
		cout << (num_instruction == last_reset_time) << " | " << min_class << ' ' << setw(2) << min_class_frame << ' ' << i << endl;
	return f_table->At(min_class_frame);
}
