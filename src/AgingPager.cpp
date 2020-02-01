/*
 * AgingPager.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: sungw
 */

#include "AgingPager.h"


AgingPager::AgingPager(int num_frame, Process* proc[]) : Pager(num_frame), proc(proc) {
	hand = -1;
}

Frame* AgingPager::select_victim_frame(unsigned long num_instruction) {
	int frame_size = f_table->GetMaxNum();
	hand = (hand + 1) % frame_size;
	int i = 0;

	if (doAging)
		cout << "ASELECT " << hand << '-' << (hand + frame_size - 1) % frame_size << " | ";

	//shift age bit to the right one time and if it is referenced, unset the "R" bit and set the left most bit to 1
	while (i++ < frame_size) {
		f_table->At(hand)->ShiftAge();
		if (proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsReferenced()) {
			proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->UnSetReferenced();
			f_table->At(hand)->SetAgeBit();
		}
		hand = (hand + 1) % frame_size;
	}

	int youngest_frame_num = hand;
	unsigned long youngest_age = f_table->At(hand)->GetAge();
	i = 0;
	//find the frame with youngest age bits
	while (i++ < frame_size) {
		if (doAging)
			cout << hand << ':' << hex << f_table->At(hand)->GetAge() << ' ' << dec;
		hand = (hand + 1) % frame_size;
		if (f_table->At(hand)->GetAge() < youngest_age) {
			youngest_age = f_table->At(hand)->GetAge();
			youngest_frame_num = hand;
		}
	}
	hand = youngest_frame_num;
	f_table->At(youngest_frame_num)->UnSetAgeBit(); // set the selected frame's age bit to zero

	if (doAging)
		cout << "| " << youngest_frame_num << endl;

	return f_table->At(youngest_frame_num);
}
