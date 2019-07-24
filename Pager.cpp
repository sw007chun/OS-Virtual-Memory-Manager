/*
 * Pager.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#include "Pager.h"

//Pager::Pager (FrameTable* frame_table) {
//	f_table = frame_table;
//}
Pager::Pager (int num_frame) {
	f_table = new FrameTable(num_frame);
}
Frame* Pager::GetFrame() {
	Frame *new_frame = f_table->GetFreeFrame();
	if (new_frame == NULL)
		new_frame = select_victim_frame();
	return new_frame;
}
void Pager::PrintFrameTable() {
	f_table->PrintFrameTable();
}
void Pager::SetFree(int frame_num) {
	f_table->SetFree(frame_num);
}
//void Pager::SetReferenced(int frame_num) {
//	f_table->At(frame_num)->SetReferenced();
//}
