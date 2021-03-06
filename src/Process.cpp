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
	p_table = new PTE*[MAX_PTE]();	//individual page entry is initially null before 1st page fault
}
Process::~Process() {
	for (int i = 0; i < MAX_PTE; i++) {
		if (p_table[i] != NULL )
			delete[] p_table[i];
	}
	delete[] p_table;
}
int Process::GetPID() {
	return pid;
}
PTE* Process::GetVPage(int v_page_num) {
	if (p_table[v_page_num] == NULL) {	//if it is 1st page fault
		list<vma *>::iterator it;
		p_table[v_page_num] = new PTE();	//declare a page entry
		for (it = vma_list->begin(); it != vma_list->end(); it++) {
			if (v_page_num >= (*it)->start_page && v_page_num <= (*it)->end_page) {	//find corresponding VMA
				//set up write protected and file map bits
				if ((*it)->write_protected)
					p_table[v_page_num]->SetWriteProtected();
				if ((*it)->filemap)
					p_table[v_page_num]->SetFileMapped();
				break;
			}
		}
		if (it == vma_list->end()) {	//if no corresponding bit is found set segmentation fault bit
			p_table[v_page_num]->SetSEGV();
		}
	}
	return p_table[v_page_num];
}
void Process::ExitProcess(Pager *pager) {
	cout << "EXIT current process " << pid << endl;
	for (int i = 0; i < MAX_PTE; i++) {
		if (p_table[i] != NULL ) {	//check if page entry has been declared
			if (p_table[i]->IsPresent()) {	//check if page entry is mapped into frame
				UnSetPresent(i);
				if (IsModified(i) && IsFileMapped(i))
						FileOut();
				pager->SetFree(p_table[i]->GetPageFrame());	//free up frame from the virtual page entry
			}
			if (p_table[i]->IsPagedOut())
				p_table[i]->UnSetPagedOut();
		}
	}
}
void Process::SetPage(int v_page_num, int frame_num) {
	p_table[v_page_num]->SetPresent();
	p_table[v_page_num]->SetPageFrame(frame_num);
	p_table[v_page_num]->SetReferenced();
	p_stat.maps++;
	trace (" MAP " << frame_num);
}
void Process::SetPagedOut(int v_page_num) {
	p_table[v_page_num]->SetPagedOut();
	p_stat.outs++;
	trace (" OUT");
}
void Process::UnSetPresent(int v_page_num) {
	p_table[v_page_num]->UnSetPresent();
	p_stat.unmaps++;
	trace(" UNMAP " << pid << ':' << v_page_num);
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
void Process::SEGV() {
	p_stat.segv++;
	trace (" SEGV");
}
void Process::SEGProt() {
	p_stat.segprot++;
	trace(" SEGPROT");
}
void Process::FileOut() {
	p_stat.fouts++;
	trace (" FOUT");
}
void Process::FileIn() {
	p_stat.fins++;
	trace (" FIN");
}
void Process::SwapIn() {
	p_stat.ins++;
	trace (" IN");
}
void Process::Zero() {
	p_stat.zeros++;
	trace (" ZERO");
}
void Process::PrintProc() {
	cout << "PROC[" << pid << "]: U=" << p_stat.unmaps << " M=" << p_stat.maps << " I=" << p_stat.ins << " O=" << p_stat.outs <<
			 " FI=" << p_stat.fins << " FO=" << p_stat.fouts << " Z=" << p_stat.zeros << " SV=" << p_stat.segv << " SP=" << p_stat.segprot << endl;
}
void Process::PrintProcTable() {
	cout << "PT[" << pid << "]:";
	for (int j = 0; j < MAX_PTE; j++) {
		cout << ' ';
		if (GetVPage(j) != NULL) {
			if (GetVPage(j)->IsPresent()) {
				cout << j << ':';
				if (GetVPage(j)->IsReferenced())
					cout << "R";
				else
					cout << '-';
				if (GetVPage(j)->IsModified())
					cout << "M";
				else
					cout << '-';
				if (GetVPage(j)->IsPagedOut())
					cout << "S";
				else
					cout << '-';
			} else if (GetVPage(j)->IsPagedOut()) {
				cout << '#';
			} else {
				cout << '*';
			}
		} else {
			cout << '*';
		}
	}
	cout << endl;
}
unsigned long long Process::Cost() {
	const int kMapCost = 400;
	const int kPageCost = 3000;
	const int kFileCost = 2500;
	const int kZeroCost = 150;
	const int kSEGVCost = 240;
	const int kSEGPROTCost = 300;

	unsigned long long proc_cost = (p_stat.unmaps + p_stat.maps) * kMapCost;
	proc_cost += (p_stat.ins + p_stat.outs) * kPageCost;
	proc_cost += (p_stat.fins + p_stat.fouts) * kFileCost;
	proc_cost += p_stat.zeros * kZeroCost + p_stat.segv * kSEGVCost + p_stat.segprot * kSEGPROTCost;
	return proc_cost;
}
