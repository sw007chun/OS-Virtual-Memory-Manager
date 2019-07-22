/*
 * PageTableEntry.h
 *
 *  Created on: Jul 21, 2019
 *      Author: sungw
 */

#ifndef PAGETABLEENTRY_H_
#define PAGETABLEENTRY_H_

#define MAX_PTE (64)

typedef struct pte {
	unsigned present:1;
	unsigned write_protected:1;
	unsigned modified:1;
	unsigned referenced:1;
	unsigned pagedout:1;
	unsigned p_frame:5;
	unsigned segv:1;
	unsigned file_mapped:1;
	pte(unsigned wp, unsigned fm) {
		present = 0;
		write_protected = wp;
		modified = 0;
		referenced = 0;
		pagedout = 0;
		p_frame = 0;
		segv = 0;
		file_mapped = fm;
	}
} pte;


#endif /* PAGETABLEENTRY_H_ */
