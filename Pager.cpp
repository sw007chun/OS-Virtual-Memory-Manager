/*
 * Pager.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#include "Pager.h"

Pager::Pager (int num_frame) {
	f_table = new FrameTable(num_frame);
}
Frame* Pager::GetFrame(int num_instruction) {
	Frame *new_frame = f_table->GetFreeFrame();
	if (new_frame == NULL)
		new_frame = select_victim_frame(num_instruction);
	else
		new_frame->SetLastUsed(num_instruction);
	return new_frame;
}
void Pager::PrintFrameTable() {
	f_table->PrintFrameTable();
}
void Pager::SetFree(int frame_num) {
	f_table->SetFree(frame_num);
}
Pager::~Pager() {
	delete f_table;
}
