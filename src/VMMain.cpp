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

int dotrace = 0; //variable for -O option, mostly done in Process.cpp
int doAging = 0; //variable for -a option, mostly done in individual pagers

int main(int argc, char* argv[]) {
	int c, num_Process, num_frame;
	char algo;
	char *option;
	ifstream input_file, random_file;

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
			dotrace = true;
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
			doAging = true;
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

	//getting random file
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

	//getting vma information and declaring processes
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
	//counters for number of instructions
	unsigned long num_instruction = 0;
	unsigned long context_switches = 0;
	unsigned long process_exits = 0;

	//actual simulation code
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
			page_entry = current_process->GetVPage(inst_num);	//retrieving virtual page of r/w command

			if(page_entry->IsSEGV()) {	//check segmentation violation and pass rest of command if it is
				current_process->SEGV();
				continue;
			}

			if (!page_entry->IsPresent()) {	//if page entry is not mapped to a page frame
				new_frame = pager->GetFrame(num_instruction);	//find a frame to map the virtual page into

				if (new_frame->IsMapped()) {	//if the frame to be mapped is mapped to another virtual page
					//get the associated process number and v_page number of previously mapped page entry
					int old_pid = new_frame->GetPID();
					int old_page_num = new_frame->GetVPageNum();

					proc[old_pid]->UnSetPresent(old_page_num);	//unset the present bit of previously mapped v_page

					if (proc[old_pid]->IsModified(old_page_num)) {	//if previous mapped page has been modified
						proc[old_pid]->UnSetModified(old_page_num);	//unset modified bit
						if (proc[old_pid]->IsFileMapped(old_page_num))	//if it is file mapped
							proc[old_pid]->FileOut();	//file out the page
						else
							proc[old_pid]->SetPagedOut(old_page_num);	//if not page out to swap device
					}
				}

				//check if newly mapped v_page is file mapped
				if (current_process->IsFileMapped(inst_num))
					current_process->FileIn();
				else if (current_process->IsPagedOut(inst_num))
					current_process->SwapIn();
				else
					current_process->Zero();

				//set the frame with new v_page information and set new v_page with current frame number
				new_frame->SetPage(current_process->GetPID(), inst_num);
				current_process->SetPage(inst_num, new_frame->GetFrameNum());
			} else {
				//if v_page is mapped to a frame just set reference bit to 1, mostly for clock algorithm
				page_entry->SetReferenced();
			}

			//if it was a write instruction check if the VMA is write protected if not set modified bit
			if (instruction == 'w') {
				if (page_entry->IsWriteProtected())
					current_process->SEGProt();
				else
					page_entry->SetModified();
			}

			//these are to print current status  options
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
			proc[inst_num]->ExitProcess(pager);	//exit process passing pager to free frames from current process' v_page
			process_exits++;
			break;
		default:
			break;
		}
	}

	//print final results
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
	delete pager;
}


