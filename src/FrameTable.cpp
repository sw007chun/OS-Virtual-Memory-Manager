/*
 * FrameTable.cpp
 *
 *  Created on: Jul 21, 2019
 *      Author: sungw
 */

#include "FrameTable.h"

FrameTable::FrameTable(int num) {
	max_num_frame = num;
	f_table = new Frame[max_num_frame];
	//setting frame number and pushing it into the free frame queue
	for (int i = 0; i < max_num_frame; i++) {
		f_table[i].SetFrameNum(i);
		free_q.push(&f_table[i]);
	}
}
FrameTable::~FrameTable() {
	delete[] f_table;
}
Frame* FrameTable::GetFreeFrame() {
	if (!free_q.empty()) {
		Frame *frame = free_q.front();
		free_q.pop();
		return frame;
	} else {
		return NULL;
	}
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
	f_table[frame_num].UnSetAgeBit();
	free_q.push(&f_table[frame_num]);
}
