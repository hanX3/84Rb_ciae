#include "set.hh"
#include "Sort.hh"

#include "TString.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

//
int main(int argc, char *argv[])
{
  TString raw_file_path = RAWFILEPATH;
  TString out_file_path = OUTFILEPATH;
  TString file_name = RAWFILENAME;

  if(argc != 2){
    std::cout << "error(argc != 2) " << argv[0] << "  [RunNnumber] " << std::endl;
    return 1;
  }

  TString run_number_str(argv[1]);
  int run_number = run_number_str.Atoi();

  Sort *tran = new Sort(raw_file_path, out_file_path, file_name, run_number);

  tran->GetCalPar();
  tran->Process();
  
  delete tran;
  return 0;
}
