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

typedef struct {
	int start_page;
	int end_page;
	bool write_protected;
	bool filemap;
} vma;

typedef struct pstat {
	unsigned unmaps;
	unsigned maps;
	unsigned ins;
	unsigned outs;
	unsigned fins;
	unsigned fouts;
	unsigned zeros;
	unsigned segv;
	unsigned segprot;
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
	vma *vma_array;
	pte **p_table;
public:
	Process (int p_num, vma vma_array[]);
	int GetPID();
	pte* GetVPage(int v_page_num);
	void SetModified(int v_page_num);
	void UnsetModified(int v_page_num);
	bool IsModified(int v_page_num);
	void SetPagedOut(int v_page_num);
	bool IsPagedOut(int v_page_num);
//	void SetUnmaps();
//	void SetMaps();
//	void SetIn();
//	void SetOut();
//	void SetZero();
//	void SetSegv();
//	void SetSegProt();
};

#endif /* PROCESS_H_ */

