/*
 * FrameTable.cpp
 *
 *  Created on: Jul 21, 2019
 *      Author: sungw
 */

#include "FrameTable.h"

FrameTable::FrameTable(int num) {
	max_num_frame = num;
	cur_num_frame = -1;
	f_table = new Frame[max_num_frame];
	for (int i = 0; i < max_num_frame; i++) {
		f_table[i].SetFrameNum(i);
		free_q.push(&f_table[i]);
	}
}
Frame* FrameTable::GetFreeFrame() {
	if (!free_q.empty()) {
		Frame *frame = free_q.front();
		free_q.pop();
		return frame;
	} else {
		return NULL;
	}
//	if (cur_num_frame < max_num_frame - 1) {
//		cur_num_frame++;
//		f_table[cur_num_frame].SetFrameNum(cur_num_frame);
//		return &f_table[cur_num_frame];
//	}
//	else
//		return NULL;
}
Frame* FrameTable::At(int frame_num) {
	return &f_table[frame_num];
}
int FrameTable::GetMaxNum() {
	return max_num_frame;
}
void FrameTable::PrintFrameTable(){
	cout << "FT:";
	for (int i = 0; i < max_num_frame; i++) {
		cout << ' ';
		if (f_table[i].IsMapped())
			cout << f_table[i].GetPID() << ':' << f_table[i].GetVPageNum();
		else
			cout << '*';
	}
	cout << endl;
}
void FrameTable::SetFree(int frame_num) {
	f_table[frame_num].SetFree();
	free_q.push(&f_table[frame_num]);
//	for (int i = 0; i < max_num_frame; i++) {
//		f_table[i].SetFree();
//		free_q.push(&f_table[i]);
//		cout << " UNMAP " << process_num << ':' << f_table[i].GetVPageNum() << endl;
//	}
}
