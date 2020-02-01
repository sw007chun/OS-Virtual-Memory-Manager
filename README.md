# OS-Virtual-Memory-Manager

Implementation/simulation the operation of an Operating System’s Virtual Memory Manager that maps the virtual address spaces of multiple processes onto physical frames using page table translation.


# How to run the program
./mmu [-a<algo>] [-o<options>] [–f<num_frames>] inputfile randomfile (optional arguments in any order).
  
e.g. ./mmu –ac –o[OPFS] infile rfile selects the Clock Algorithm and creates output for operations
  
| Algorithm     | Based on Physical Frames|       
| ------------- |:-------------:| 
| FIFO  |  f |
| Random | r |
| Clock | c |
| Enhanced Second Chance / NRU | e|
| Aging | a|
| Working Set | w|
