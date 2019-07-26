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
//	Frame();
//	unsigned is_new:1;
	unsigned frame_num:7;
	unsigned pid:4;
	unsigned v_page_num:6;
	unsigned is_mapped:1;
	unsigned long age:32;
	unsigned long last_used:32;
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
//	bool IsReferenced();
//	void SetReferenced();
//	void UnSetReferenced();
//	void SetPID(int pid);
//	void SetVPage(int v_page);
//	void SetMapped();
};
#endif /* FRAME_H_ */
