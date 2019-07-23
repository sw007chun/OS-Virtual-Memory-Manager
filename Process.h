/*
 * Process.h
 *
 *  Created on: Jul 20, 2019
 *      Author: sungw
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include <iostream>
#include <list>
#include "PageTableEntry.h"
using namespace std;

typedef struct vma {
	int start_page;
	int end_page;
	bool write_protected;
	bool filemap;
//	vma () {
//		start_page = 0;
//		end_page = 0;
//		write_protected = 0;
//		filemap = 0;
//	}
} vma;

typedef struct pstat {
	unsigned long unmaps;
	unsigned long maps;
	unsigned long ins;
	unsigned long outs;
	unsigned long fins;
	unsigned long fouts;
	unsigned long zeros;
	unsigned long segv;
	unsigned long segprot;
	pstat() {
		unmaps = 0;
		maps = 0;
		ins = 0;
		outs = 0;
		fins = 0;
		fouts = 0;
		zeros = 0;
		segv = 0;
		segprot = 0;
	}
} pstat;

class Process {
private:
	int pid;
	pstat p_stat;
	list <vma*> *vma_list;
	PTE **p_table;
public:
	Process (int p_num, list <vma *> *vma_list);
//	Process (int p_num, vma vma_array[]);
	int GetPID();
	PTE* GetVPage(int v_page_num);
	void SetPresent(int v_page_num);
	void SetModified(int v_page_num);
	void SetPagedOut(int v_page_num);
	void SetSegv();
	void UnSetPresent(int v_page_num);
	void UnSetModified(int v_page_num);
	bool IsModified(int v_page_num);
	bool IsPagedOut(int v_page_num);
	bool IsFileMapped(int v_page_num);
	void SEGProt();
	void FileOut();
	void FileIn();
	void SwapIn();
	void Zero();
	void PrintProc();
	unsigned long long Cost();
//	void SetSegProt();
};

#endif /* PROCESS_H_ */

