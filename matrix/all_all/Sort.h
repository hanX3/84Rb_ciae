#ifndef _SORT_H_
#define _SORT_H_

#include "set.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TROOT.h"
#include "TBenchmark.h"
#include "TH2.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TSystem.h"
#include <fstream>
#include <cstdlib>
#include <cstdio>

//
class Sort
{
public:
  Sort(TString raw, TString out, TString name, int number);
  virtual ~Sort();

  bool GetCalPar();
  void Process();
  
private:
  void ClearOpt();
  void InitEvent();
  void ProcessEntry();
  void Addback();
  void FillMatrix();
  
private:
  TFile *file_in;
  TTree *tr_in;
  Long64_t total_entry;

  Short_t slot;
  Short_t channel;
  UShort_t energy;
  Long64_t ts_real;
  Bool_t pile_up;
  Bool_t out_range;

private:
  TFile *file_out;
  Long64_t nevt;
  
  char temp_file_name[1024];
  int run_no;
  Long64_t ts_init;
  Long64_t ts_now;

  TBenchmark *benchmark;
  TRandom *ran;

private:
  double cali_par0[Crate0num][16], cali_par1[Crate0num][16], cali_par2[Crate0num][16];
  
  bool event_flag;
  double temp_energy;
  int hit_num;
  int event_slot[100];
  int event_channel[100];
  double event_energy[100];
  long long event_ts[100];
  
  TH2I *matrix;
};

#endif