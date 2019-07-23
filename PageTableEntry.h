/*
 * PageTableEntry.h
 *
 *  Created on: Jul 21, 2019
 *      Author: sungw
 */

#ifndef PAGETABLEENTRY_H_
#define PAGETABLEENTRY_H_

#define MAX_PTE (64)

class PTE {
private:
	unsigned present:1;
	unsigned write_protected:1;
	unsigned modified:1;
	unsigned referenced:1;
	unsigned paged_out:1;
	unsigned p_frame:7;
	unsigned segv:1;
	unsigned file_mapped:1;
public:
	PTE();
	void SetPresent();
	void UnSetPresent();
	void SetWriteProtected();
	void SetModified();
	void UnSetModified();
	void SetReferenced();
	void UnSetReferenced();
	void SetPagedOut();
	void SetPageFrame(int p_frame_num);
	void SetSEGV();
	void SetFileMapped();
	bool IsPresent();
	bool IsWriteProtected();
	bool IsModified();
	bool IsReferenced();
	bool IsPagedOut();
	int GetPageFrame();
	bool IsSEGV();
	bool IsFiledMapped();

};


#endif /* PAGETABLEENTRY_H_ */
