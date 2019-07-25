/*
 * Frame.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: sungw
 */

#include "Frame.h"

Frame::Frame() {
	frame_num = 0;
	pid = 0;
	v_page_num = 0;
	is_mapped = 0;
	age_last_use = 0;
}
int Frame::GetFrameNum() {
	return frame_num;
}
int Frame::GetPID() {
	return pid;
}
int Frame::GetVPageNum() {
	return v_page_num;
}
bool Frame::IsMapped() {
	return is_mapped;
}
void Frame::SetFrameNum(int frame) {
	frame_num = frame;
}
void Frame::SetPage(int pid, int v_page) {
	this->pid = pid;
	v_page_num = v_page;
	is_mapped = true;
//	is_referenced = true;
}
void Frame::SetFree() {
	is_mapped = false;
}
void Frame::ShiftAge() {
	age_last_use = age_last_use >> 1;
}
void Frame::SetAgeBit() {
	age_last_use = (age_last_use | 0x80000000);
}
void Frame::UnSetAgeBit() {
	age_last_use = 0;
}
unsigned long Frame::GetAge() {
	return age_last_use;
}
void Frame::SetLastUsed(int current_time) {
	age_last_use = current_time;
}
//bool Frame::IsReferenced() {
//	return is_referenced;
//}
//void Frame::SetReferenced() {
//	is_referenced = true;
//}
//void Frame::UnSetReferenced() {
//	is_referenced = false;
//}
//void Frame::SetPID(int pid) {
//	this->pid = pid;
//}
//void Frame::SetVPage(int v_page) {
//	v_page_num = v_page;
//}
//void Frame::SetMapped() {
//	is_mapped = 1;
//}
