/*
 * Frame.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: sungw
 */

#include "Frame.h"

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
void Frame::SetPID(int pid) {
	this->pid = pid;
}
void Frame::SetVPage(int v_page) {
	v_page_num = v_page;
}
void Frame::SetMapped() {
	is_mapped = 1;
}
