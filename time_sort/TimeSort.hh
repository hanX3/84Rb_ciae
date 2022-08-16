#ifndef _TIMESORT_H_
#define _TIMESORT_H_

#include "set.hh"

#include "TString.h"

#include<map>
#include <vector>
#include <algorithm>
#include<iostream>
#include <map>
class TBranch;
class TFile;
class TTree;
class TBenchmark;

//
struct EventData
{
  Short_t slot;
  Short_t channel;
  UShort_t energy;
  Long64_t ts_real;
  Bool_t pile_up;
  Bool_t out_range;
};

//
class TimeSort
{
public:
  TimeSort(int run_number);
  virtual ~TimeSort();

  void Process();

private:
  Short_t ts_offset[256];
  UShort_t ch_low[256];
  UShort_t ch_high[256];

private:
  std::map<Long64_t, EventData> map_sort_data;
  std::map<Long64_t, EventData>::iterator it;

private:
  //old root
  TFile *file_in;
  TTree *tr_in;

  Short_t  sr;
  Bool_t pileup;
  Bool_t outofr;
  Short_t sid;
  Short_t ch;
  UShort_t evte;
  Long64_t ts;
  Short_t cfd;
  Bool_t cfdft;
  Short_t cfds;

private:
  //new root
  TFile *file_out;
  TTree *tr_out;

  EventData ed_value;

private:
  TBenchmark *benchmark;
  
  Long64_t key;
  Long64_t total_entry;
  Long64_t current_entry;
};

#endif