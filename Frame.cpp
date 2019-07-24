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
//	is_referenced = 0;
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
