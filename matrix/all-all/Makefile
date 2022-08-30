OBJ = event
sourcefile = main.cc Sort.hh Sort.cc set.hh

ROOTCFLAGS  = $(shell root-config --cflags)
ROOTLIBS    = $(shell root-config --libs)

CFLAGS = -g -Wall -O2 -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

GXX = g++ 

all:$(OBJ)

$(OBJ): $(sourcefile)
	$(GXX) $(CFLAGS) $(ROOTCFLAGS) -o $@ $(filter %.cc, $(sourcefile)) $(ROOTLIBS)

clean:
	rm -f *~ *.o $(OBJ)