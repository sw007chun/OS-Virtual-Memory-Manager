/*
 * Process.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#include "Process.h"

Process::Process (int p_num, vma vma_array[]) {
	pid = p_num;
	this->vma_array = vma_array;
	p_table = new pte*[MAX_PTE]();
}
int Process::GetPID() {
	return pid;
}
pte* Process::GetVPage(int v_page_num) {
	if (p_table[v_page_num] == NULL) {
		int i = 0;
		while (vma_array[i] != NULL) {
			if (v_page_num >= vma_array[i].start_page && v_page_num <= vma_array[i].end_page) {
				p_table[v_page_num] = new pte(vma_array[i].write_protected, vma_array[i].filemap);
			}
			i++;
		}
	}
	return p_table[v_page_num];
}
void Process::SetModified(int v_page_num) {
	p_table[v_page_num]->modified = 1;
}
void Process::UnsetModified(int v_page_num) {
	p_table[v_page_num]->modified = 0;
}
bool Process::IsModified(int v_page_num) {
	return p_table[v_page_num]->modified;
}
void Process::SetPagedOut(int v_page_num) {
	p_table[v_page_num]->pagedout = 1;
	p_stat.outs++;
}
bool Process::IsPagedOut(int v_page_num) {
	return p_table[v_page_num]->pagedout;
}

//void Process::SetUnmaps() {
//	pstat.unmaps++;
//}
//void Process::SetMaps() {
//	pstat.maps++;
//}
//void Process::SetIn();
//void Process::SetOut();
//void Process::SetZero();
//void Process::SetSegv();
//void Process::SetSegProt();
