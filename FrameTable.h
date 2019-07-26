/*
 * FrameTable.h
 *
 *  Created on: Jul 21, 2019
 *      Author: sungw
 */

#ifndef FRAMETABLE_H_
#define FRAMETABLE_H_

#include <iostream>
#include <queue>
#include "Frame.h"
using namespace std;

class FrameTable {
private:
	Frame* f_table;
	queue <Frame *> free_q;
	int max_num_frame;
	int cur_num_frame;
public:
	FrameTable(int num);
	~FrameTable();
	Frame* GetFreeFrame();
	Frame* At(int frame_num);
	int GetMaxNum();
	void PrintFrameTable();
	void SetFree(int frame_num);
};



#endif /* FRAMETABLE_H_ */
