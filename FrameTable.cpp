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
}
Frame* FrameTable::GetFreeFrame() {
	if (cur_num_frame < max_num_frame - 1) {
		cur_num_frame++;
		f_table[cur_num_frame].SetFrameNum(cur_num_frame);
		return &f_table[cur_num_frame];
	}
	else
		return NULL;
}
Frame* FrameTable::GetAt(int frame_num) {
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
