/*
 * WSPager.cpp
 *
 *  Created on: Jul 25, 2019
 *      Author: sungw
 */

#include "WSPager.h"

WSPager::WSPager(int num_frame, Process* proc[]) : Pager(num_frame), proc(proc) {
	hand = -1;
}

Frame* WSPager::select_victim_frame(unsigned long num_instruction) {
	int frame_size = f_table->GetMaxNum();
	hand = (hand + 1) % frame_size;
	unsigned long oldest_age = num_instruction - f_table->At(hand)->GetLastUsed();
	int oldest_frame = hand;
	//is_ref is a flag to check if the first frame to start checking is with "R" bit set to 1 and oldest frame
	//if there is a frame with younger than first hand frame, such frame should be selected
	bool is_ref = proc[f_table->At(oldest_frame)->GetPID()]->GetVPage(f_table->At(oldest_frame)->GetVPageNum())->IsReferenced();
	int i = 0;

	if (doAging)
		cout << "ASELECT " << hand << '-' << (hand + frame_size - 1) % frame_size << " |";

	while (i++ < frame_size) {
		if (doAging)
			cout  << ' ' << hand << '(' << proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsReferenced()
			<< ' ' << f_table->At(hand)->GetPID() << ':' << f_table->At(hand)->GetVPageNum() << ' ' << f_table->At(hand)->GetLastUsed() - 1 << ')';

		//if "R" bit is set, unset "R" bit and set last used time to current time
		if (proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->IsReferenced()) {
				proc[f_table->At(hand)->GetPID()]->GetVPage(f_table->At(hand)->GetVPageNum())->UnSetReferenced();
				f_table->At(hand)->SetLastUsed(num_instruction);
		} else {
			//if frame with "R" bit 0 and time past from last used time is over TAU stop finding the frame
			if (num_instruction - f_table->At(hand)->GetLastUsed() > TAU) {
				oldest_frame = hand;
				f_table->At(hand)->SetLastUsed(num_instruction);
				if (doAging)
					cout << " STOP(" << i << ')';
				break;
			} else {
				if (num_instruction - f_table->At(hand)->GetLastUsed() > oldest_age || is_ref) {
					oldest_frame = hand;
					oldest_age = num_instruction - f_table->At(hand)->GetLastUsed();
					is_ref = false;
				}
			}
		}
		hand = (hand + 1) % frame_size;
	}
	f_table->At(oldest_frame)->SetLastUsed(num_instruction);
	hand = oldest_frame;
	if (doAging)
		cout << " | " << oldest_frame << endl;
	return f_table->At(oldest_frame);
}



