/*
 * Process.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#include "Process.h"

Process::Process (int p_num, list <vma *> *vma_list) {
	pid = p_num;
	this->vma_list = vma_list;
	p_table = new PTE*[MAX_PTE]();
}
int Process::GetPID() {
	return pid;
}
PTE* Process::GetVPage(int v_page_num) {
	if (p_table[v_page_num] == NULL) {
		list<vma *>::iterator it;
		p_table[v_page_num] = new PTE();
		for (it = vma_list->begin(); it != vma_list->end(); it++) {
			if (v_page_num >= (*it)->start_page && v_page_num <= (*it)->end_page) {
				if ((*it)->write_protected)
					p_table[v_page_num]->SetWriteProtected();
				if ((*it)->filemap)
					p_table[v_page_num]->SetFileMapped();
				break;
			}
		}
		if (it == vma_list->end()) {
			p_table[v_page_num]->SetSEGV();
			p_stat.segv++;
		}
	}
	return p_table[v_page_num];
}
void Process::SetPresent(int v_page_num) {
	p_table[v_page_num]->SetPresent();
	p_stat.maps++;
}
void Process::SetModified(int v_page_num) {
	p_table[v_page_num]->SetModified();
}
void Process::SetPagedOut(int v_page_num) {
	p_table[v_page_num]->SetPagedOut();
	p_stat.outs++;
}
void Process::UnSetPresent(int v_page_num) {
	p_table[v_page_num]->UnSetPresent();
	p_stat.unmaps++;
}
void Process::UnSetModified(int v_page_num) {
	p_table[v_page_num]->UnSetModified();
}
bool Process::IsModified(int v_page_num) {
	return p_table[v_page_num]->IsModified();
}
bool Process::IsPagedOut(int v_page_num) {
	return p_table[v_page_num]->IsPagedOut();
}
bool Process::IsFileMapped(int v_page_num) {
	return p_table[v_page_num]->IsFiledMapped();
}
void Process::SEGProt() {
	p_stat.segprot++;
}
void Process::FileOut() {
	p_stat.fouts++;
}
void Process::FileIn() {
	p_stat.fins++;
}
void Process::SwapIn() {
	p_stat.ins++;
}
void Process::Zero() {
	p_stat.zeros++;
}
void Process::PrintProc() {
	cout << "PROC[" << pid << "]: U=" << p_stat.unmaps << " M=" << p_stat.maps << " I=" << p_stat.ins << " O=" << p_stat.outs <<
			 " FI=" << p_stat.fins << " FO=" << p_stat.fouts << " Z=" << p_stat.zeros << " SV=" << p_stat.segv << " SP=" << p_stat.segprot << endl;
}

unsigned long long Process::Cost() {
	const int kMapCost = 400;
	const int kPageCost = 3000;
	const int kFileCost = 2500;
	const int kZeroCost = 150;
	const int kSEGVCost = 240;
	const int kSEGPROTCost = 300;

	unsigned long long proc_cost = (p_stat.unmaps + p_stat.maps)*kMapCost;
	proc_cost += (p_stat.ins + p_stat.outs)*kPageCost;
	proc_cost += (p_stat.fins + p_stat.fouts)*kFileCost;
	proc_cost += p_stat.zeros*kZeroCost + p_stat.segv*kSEGVCost + p_stat.segprot*kSEGPROTCost;
	return proc_cost;
}
