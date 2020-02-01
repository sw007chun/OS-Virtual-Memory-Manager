# OS-Virtual-Memory-Manager

Implementation/simulation the operation of an Operating System’s Virtual Memory Manager that maps the virtual address spaces of multiple processes onto physical frames using page table translation.


# How to run the program
./mmu [-a<algo>] [-o<options>] [–f<num_frames>] inputfile randomfile (optional arguments in any order).
e.g. ./mmu –ac –o[OPFS] infile rfile selects the Clock Algorithm and creates output for operations
  
  
 Algorithm
FIFO    f
Random  r
Clock   c
Enhanced Second Chance / NRU  e
Aging   a
Working Set w
  
• The ‘O’ (ohhh) option shall generate the required output as shown in output-1/3.
• The ‘P’ (pagetable option) should print after the execution of all instructions the state of the pagetable: As a single line for each process, you print the content of the pagetable pte entries as follows: PT[0]: 0:RMS 1:RMS 2:RMS 3:R-S 4:R-S 5:RMS 6:R-S 7:R-S 8:RMS 9:R-S 10:RMS 11:R-S 12:R-- 13:RM- # # 16:R-- 17:R-S # # 20:R-- # 22:R-S 23:RM- 24:RMS # # 27:R-S 28:RMS # # # # # 34:R-S 35:R-S # 37:RM- 38:R-S * # 41:R-- # 43:RMS 44:RMS # 46:R-S * * # * * * # 54:R-S # * * 58:RM- * * # * * R (referenced), M (modified), S (swapped out) (note we don’t show the write protection bit as it is implied/inherited from the specified VMA. Pages that are not valid are represented by a ‘#’ if they have been swapped out (note you don’t have to swap out a page if it was only referenced but not modified), or a ‘*’ if it does not have a swap area associated with. Otherwise (valid) indicates the virtual page index and RMS bits with ‘-‘ indicated that that bit is not set.
Note a virtual page, that was once referenced, but was not modified and then is selected by the replacement algorithm, does not have to be paged out (by definition all content must still be ZERO) and can transition to ‘*’.
• The ‘F’ (frame table option) should print after the execution and should show which frame is mapped at the end to which <pid:virtual page> or ‘*’ if not currently mapped by any virtual page. FT: 0:32 0:42 0:4 1:8 * 0:39 0:3 0:44 1:19 0:29 1:61 * 1:58 0:6 0:27 1:34
• The ‘S’ option prints the summary line (“SUM …”) described above.
• The ‘x’ options prints the current page table after each instructions (see example outputs) and this should help you significantly to track down bugs and transitions
• The ‘y’ option is like ‘x’ but prints the page table of all processes instead.
• The ‘f’ option prints the frame table after each instruction.
• The ‘a’ option prints additional “aging” information during victim_select and after each instruction for complex algorithms (not all algorithms have the details described in more detail below)
