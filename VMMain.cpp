/*
 * VMMain.cpp
 *
 *  Created on: Jul 19, 2019
 *      Author: sungw
 */

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <list>
#include "Pager.h"
#include "FIFOPager.h"
#include "Process.h"
#include "FrameTable.h"
using namespace std;

int dotrace = 0;

#define trace(fmt...) do { if (dotrace > 0) { cout << fmt << endl; fflush(stdout); } } while (0)

Frame* get_frame(FrameTable* f_table, Pager *pager) {
	Frame* new_frame = f_table->GetFreeFrame();
	if (new_frame < 0) {
		new_frame = pager->select_victim_frame();
		trace(" UNMAP " << new_frame->frame_num << ':' << new_frame->v_page_num );
	}
	return new_frame;
}

int main(int argc, char* argv[]) {
	int c, num_Process;
	char algo;
	char *option;
	ifstream input_file;
	ifstream random_file;
	FrameTable *frame_table;

	while ((c = getopt(argc, argv, "a:o:f:")) != -1) {
		switch (c) {
		case 'a':
			algo = *optarg;
			break;
		case 'o':
			option = optarg;
			break;
		case 'f':
			frame_table = new FrameTable(atoi(optarg));
			break;
		case '?':
			break;
		default:
			break;
		}
	}

	for (int i = 0; option[i] != '\0'; i++) {
		switch (option[i]) {
		case 'O':
			dotrace = 1;
			break;
		case 'P':
			break;
		case 'F':
			break;
		case 'S':
			break;
		case 'x':
			break;
		case 'y':
			break;
		case 'f':
			break;
		case 'a':
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

	for (int i = 0; i < num_Process; i++) {
		while (getline(input_file, readline) && readline.at(0) == '#') { }
		numVMA = atoi(readline.c_str());
		vma vma_array[numVMA];

		for (int j = 0; j < numVMA; j++) {
			input_file >> vma_array[j].start_page >> vma_array[j].end_page >> vma_array[j].write_protected >> vma_array[j].filemap;
//			cout << vma_list[j].start_page << ' ' << vma_list[j].end_page << endl;
		}
		input_file.ignore();
		proc[i] = new Process(i, vma_array);
	}


	Pager* pager;

	switch (algo) {
	case 'f':
		pager = new FIFOPager(frame_table);
		break;
	case 'r':
		break;
	case 'c':
		break;
	case 'e':
		break;
	case 'a':
		break;
	case 'w':
		break;
	default :
		break;
	}

	getline(input_file, readline);

	Process *current_process;
	pte *page_entry;
	Frame *new_frame;
//	int new_frame_num;
	char instruction;
	int v_page_num;
	int num_instruction = 0;

	while (input_file >> instruction >> v_page_num) {
		trace(num_instruction << ": ==> " << instruction << ' ' << v_page_num );
		num_instruction++;
		switch (instruction) {
		case 'c':
			current_process = proc[v_page_num];
			break;
		case 'r':
		case 'w':
			page_entry = current_process->GetVPage(v_page_num);

			if (!page_entry->present) {
				new_frame = frame_table->GetFreeFrame();
				if (new_frame == NULL) {
					new_frame = pager->select_victim_frame();
					trace(" UNMAP " << new_frame->pid << ':' << new_frame->v_page_num );
					if (proc[new_frame->pid]->IsModified(new_frame->v_page_num )) {
						proc[new_frame->pid]->SetPagedOut(new_frame->v_page_num);
						proc[new_frame->pid]->UnsetModified(new_frame->v_page_num);
						trace (" OUT");
					}
				}

				if (current_process->IsPagedOut(v_page_num)) {
					trace (" IN");
				}
				else if (proc[current_process->GetPID()]->GetVPage(v_page_num)->pagedout) {
					trace (" ZERO");
				}
				new_frame->pid = current_process->GetPID();
				new_frame->v_page_num = v_page_num;
				proc[current_process->GetPID()]->GetVPage(v_page_num)->present = 1;
				trace (" MAP " << new_frame->frame_num );

				page_entry->p_frame = new_frame->frame_num;
				page_entry->referenced = 1;
				pager->add_page(page_entry);
			}

//			cout << frame_table->GetAt(page_entry->p_frame)->v_page_num << endl;
			if (instruction == 'w') {
				if (page_entry->write_protected) {
					trace(" SEGPROT");
				} else {
					page_entry->modified = 1;
				}
			}

			break;
		case 'e':
			break;
		default:
			break;
		}

	}

	delete frame_table;
	delete [] rand;
	delete pager;
}


