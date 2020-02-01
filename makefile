CC = g++

PROGRAM = mmu
ODIR = obj
SDIR = src
IDIR = include
CPPFLAGS = -I$(IDIR)

OBJ := $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(wildcard $(SDIR)/*.cpp))

$(PROGRAM): $(OBJ)
	$(CC) -g -o $@ $^ $(CPPFLAGS)

$(OBJ): |$(ODIR)

$(ODIR):
	mkdir $@

$(ODIR)/%.o : $(SDIR)/%.cpp $(IDIR)/*.h
	$(CC) -c -o $@ $< $(CPPFLAGS)

.PHONY: clean
clean:
	rm -f $(PROGRAM) *~ $(ODIR)/*.o
	rmdir $(ODIR)
