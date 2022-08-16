#include "TimeSort.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

//
int main(int argc, char *argv[])
{
  if(argc != 2) {
    std::cout << "error(argc != 2)      "<< argv[0] << "  [RunNnumber]" << std::endl;
    return 1;
  }

  TString run_number_str(argv[1]);
  int run_number = run_number_str.Atoi();
  
  TimeSort *ts = new TimeSort(run_number);
  ts->Process();
  delete ts;

  return 0;
}