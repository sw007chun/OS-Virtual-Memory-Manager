/*
 * VMMain.cpp
 *
 *  Created on: Jul 19, 2019
 *      Author: sungw
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include "Pager.h"
#include "FIFOPager.h"
#include "RandomPager.h"
#include "ClockPager.h"
#include "NRUPager.h"
#include "AgingPager.h"
#include "WSPager.h"
#include "Process.h"
#include "FrameTable.h"
using namespace std;

int dotrace = 0;
int doAging = 0;;

int main(int argc, char* argv[]) {
	int c, num_Process;
	char algo;
	char *option;
	ifstream input_file;
	ifstream random_file;
	int num_frame;

	while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
		switch (c) {
		case 'a':
			algo = *optarg;
			break;
		case 'o':
			option = optarg;
			break;
		case 'f':
			num_frame = atoi(optarg);
			break;
		case '?':
			break;
		default:
			break;
		}
	}

	bool page_table_option = false;
	bool frame_table_option = false;;
	bool summary_option = false;
	bool page_entry_option = false;
	bool all_page_entry_option = false;
	bool frame_table_each_time = false;

	for (int i = 0; option[i] != '\0'; i++) {
		switch (option[i]) {
		case 'O':
			dotrace = 1;
			break;
		case 'P':
			page_table_option = true;
			break;
		case 'F':
			frame_table_option = true;
			break;
		case 'S':
			summary_option = true;
			break;
		case 'x':
			page_entry_option = true;
			break;
		case 'y':
			all_page_entry_option = true;
			break;
		case 'f':
			frame_table_each_time = true;
			break;
		case 'a':
			doAging = 1;
			break;
		default:
			break;
		}
	}

	input_file.open(argv[optind]);
	if (!input_file.is_open()) {
		cout << "Not a valid input file: " << argv[optind] << endl;
		return  1;
	}

	string readline;
	random_file.open(argv[optind+1]);
	if (!random_file.is_open()) {
		cout << "Not a valid random file: " << argv[optind+1] << endl;
		return  1;
	}

	getline(random_file, readline);
	int rlength = atoi(readline.c_str());
	int *rand = new int[rlength];

	for (int i = 0; i < rlength; i++) {
		getline(random_file, readline);
		rand[i] = atoi(readline.c_str());
	}

	while (getline(input_file, readline) && readline.at(0) == '#') { }
	num_Process = atoi(readline.c_str());

	Process *proc[num_Process];
	int numVMA;
	list <vma *> *vma_list;

	for (int i = 0; i < num_Process; i++) {
		while (getline(input_file, readline) && readline.at(0) == '#') { }
		numVMA = atoi(readline.c_str());
		vma_list = new list <vma *>;
		for (int j = 0; j < numVMA; j++) {
			vma *new_vma = new vma();
			input_file >> new_vma->start_page >> new_vma->end_page >> new_vma->write_protected >> new_vma->filemap;
			vma_list->push_back(new_vma);
		}
		input_file.ignore();
		proc[i] = new Process(i, vma_list);
	}


	Pager* pager;

	switch (algo) {
	case 'f':
		pager = new FIFOPager(num_frame);
		break;
	case 'r':
		pager = new RandomPager(num_frame, rand, rlength);
		break;
	case 'c':
		pager = new ClockPager(num_frame, proc);
		break;
	case 'e':
		pager = new NRUPager(num_frame, proc);
		break;
	case 'a':
		pager = new AgingPager(num_frame, proc);
		break;
	case 'w':
		pager = new WSPager(num_frame, proc);
		break;
	default :
		break;
	}

	getline(input_file, readline);

	Process *current_process;
	PTE *page_entry;
	Frame *new_frame;
	char instruction;
	int inst_num;
	unsigned long num_instruction = 0;
	unsigned long context_switches = 0;
	unsigned long process_exits = 0;

	while (input_file >> instruction >> inst_num) {
		trace(num_instruction << ": ==> " << instruction << ' ' << inst_num );
		num_instruction++;
		switch (instruction) {
		case 'c':
			current_process = proc[inst_num];
			context_switches++;
			break;
		case 'r':
		case 'w':
			page_entry = current_process->GetVPage(inst_num);

			if(page_entry->IsSEGV()) {
				current_process->SEGV();
				continue;
			}

			if (!page_entry->IsPresent()) {
				new_frame = pager->GetFrame(num_instruction);

				if (new_frame->IsMapped()) {
					int old_pid = new_frame->GetPID();
					int old_page_num = new_frame->GetVPageNum();

					proc[old_pid]->UnSetPresent(old_page_num);

					if (proc[old_pid]->IsModified(old_page_num )) {
						proc[old_pid]->UnSetModified(old_page_num);
						if (proc[old_pid]->IsFileMapped(old_page_num))
							proc[old_pid]->FileOut();
						else
							proc[old_pid]->SetPagedOut(old_page_num);
					}
				}

				if (current_process->IsFileMapped(inst_num))
					current_process->FileIn();
				else if (current_process->IsPagedOut(inst_num))
					current_process->SwapIn();
				else
					current_process->Zero();

				new_frame->SetPage(current_process->GetPID(), inst_num);
				current_process->SetPage(inst_num, new_frame->GetFrameNum());
			} else {
				//for clock algo
				page_entry->SetReferenced();
			}

			if (instruction == 'w') {
				if (page_entry->IsWriteProtected())
					current_process->SEGProt();
				else
					page_entry->SetModified();
			}
			if (all_page_entry_option) {
				for (int i = 0; i < num_Process; i++)
					proc[i]->PrintProcTable();
			}
			else if (page_entry_option)
				current_process->PrintProcTable();

			if (frame_table_each_time)
				pager->PrintFrameTable();
			break;
		case 'e':
			proc[inst_num]->ExitProcess(pager);
			process_exits++;
			break;
		default:
			break;
		}
	}

	if (page_table_option) {
		for (int i = 0; i < num_Process; i++)
			proc[i]->PrintProcTable();
	}

	if (frame_table_option) {
		pager->PrintFrameTable();
	}

	if (summary_option) {
		unsigned long long total_cost = 0;
		const int kSwitchCost = 121;
		const int kExitCost = 175;
		for (int i = 0; i < num_Process; i++) {
			proc[i]->PrintProc();
			total_cost += proc[i]->Cost();
		}
		total_cost += num_instruction - context_switches - process_exits + context_switches*kSwitchCost + process_exits*kExitCost;
		cout << "TOTALCOST " << num_instruction << ' ' << context_switches << ' ' << process_exits << ' ' << total_cost << endl;
	}

	delete [] rand;
	for (int i = 0; i < num_Process; i++)
		delete proc[i];
//	delete[] proc;
	delete pager;
}


