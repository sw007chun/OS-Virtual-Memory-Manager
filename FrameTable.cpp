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
		f_table[cur_num_frame].frame_num = cur_num_frame;
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
