/*
 * Frame.h
 *
 *  Created on: Jul 22, 2019
 *      Author: sungw
 */

#ifndef FRAME_H_
#define FRAME_H_

class Frame {
private:
	unsigned frame_num:7;
	unsigned pid:4;
	unsigned v_page_num:6;
	unsigned is_mapped:1;
	unsigned long age:32;	//age info for aging algorithm
	unsigned long last_used:32;	//last used time information for working set algorithm
public:
	Frame();
	int GetFrameNum();
	int GetPID();
	int GetVPageNum();
	bool IsMapped();
	void SetFrameNum(int frame);
	void SetPage(int pid, int v_page);
	void SetFree();
	void ShiftAge();
	void SetAgeBit();
	void UnSetAgeBit();
	unsigned long GetAge();
	unsigned long GetLastUsed();
	void SetLastUsed(unsigned long  current_time);
};
#endif /* FRAME_H_ */
