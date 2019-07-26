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
	age = 0;
	last_used = 0;
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
	age = age >> 1;
}
void Frame::SetAgeBit() {
	age = (age | 0x80000000);
}
void Frame::UnSetAgeBit() {
	age = 0;
}
unsigned long Frame::GetAge() {
	return age;
}
void Frame::SetLastUsed(unsigned long current_time) {
	last_used = current_time;
}
unsigned long Frame::GetLastUsed() {
	return last_used;
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
