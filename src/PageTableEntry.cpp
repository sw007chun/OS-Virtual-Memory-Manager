/*
 * PageTableEntry.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: sungw
 */

#include "PageTableEntry.h"


PTE::PTE() {
	present = 0;
	write_protected = 0;
	modified = 0;
	referenced = 0;
	paged_out = 0;
	p_frame = 0;
	segv = 0;
	file_mapped = 0;
}

void PTE::SetPresent() {
	present = 1;
}
void PTE::UnSetPresent() {
	present = 0;
}
void PTE::SetWriteProtected() {
	write_protected = 1;
}
void PTE::SetModified() {
	modified = 1;
}
void PTE::UnSetModified() {
	modified = 0;
}
void PTE::SetReferenced() {
	referenced = 1;
}
void PTE::UnSetReferenced() {
	referenced = 0;
}
void PTE::SetPagedOut() {
	paged_out = 1;
}
void PTE::UnSetPagedOut() {
	paged_out = 0;
}
void PTE::SetPageFrame(int p_frame_num) {
	p_frame = p_frame_num;
}
void PTE::SetSEGV() {
	segv = 1;
}
void PTE::SetFileMapped() {
	file_mapped = 1;
}
bool PTE::IsPresent() {
	return present;
}
bool PTE::IsWriteProtected() {
	return write_protected;
}
bool PTE::IsModified() {
	return modified;
}
bool PTE::IsReferenced() {
	return referenced;
}
bool PTE::IsPagedOut() {
	return paged_out;
}
int PTE::GetPageFrame() {
	return p_frame;
}
bool PTE::IsSEGV() {
	return segv;
}
bool PTE::IsFiledMapped() {
	return file_mapped;
}
