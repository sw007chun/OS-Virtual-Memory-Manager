/*
 * FrameTable.h
 *
 *  Created on: Jul 21, 2019
 *      Author: sungw
 */

#ifndef FRAMETABLE_H_
#define FRAMETABLE_H_

#include <iostream>
#include "Frame.h"

class FrameTable {
private:
	Frame* f_table;
	int max_num_frame;
	int cur_num_frame;
public:
	FrameTable(int num);
	Frame* GetFreeFrame();
	Frame* GetAt(int frame_num);
	int GetMaxNum();
};



#endif /* FRAMETABLE_H_ */
