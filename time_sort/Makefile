OBJ = TimeSort
sourcefile = main.cc TimeSort.cc  TimeSort.hh set.hh


ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -Wall -g -I$(TARTSYS)/include -I$(ROOTSYS)/include -L$(TARTSYS)/lib64

GXX = g++ 

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) -o $@ $(filter %.cc ,$(sourcefile)) $(ROOTLIBS)

clean:
	rm -f *~ *.o $(OBJ)