#include "TimeSort.hh"

#include "TBranch.h"
#include "TString.h"
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TBenchmark.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string.h>

//
TimeSort::TimeSort(int run_number)
{
  current_entry = 0;
  benchmark = new TBenchmark;

  memset(ts_offset, 0, 256*sizeof(Short_t));
  memset(ch_low, 0, 256*sizeof(UShort_t));
  memset(ch_high, 0, 256*sizeof(UShort_t));
  
  std::ifstream file_par;
  file_par.open("par.dat");
  if(!file_par.is_open()){
    std::cout << "can't open file." << std::endl;
  }

  std::string str_tmp;
  getline(file_par, str_tmp);
  // std::cout<<str_tmp<<std::endl;
  Short_t sid_tmp;
  Short_t ch_tmp;
  Short_t offset_tmp;
  UShort_t ch_low_tmp;
  UShort_t ch_high_tmp;
  while(!file_par.eof()){
    file_par >> sid_tmp >> ch_tmp >> offset_tmp >> ch_low_tmp >> ch_high_tmp;
    if(file_par.eof()) break;
    ts_offset[(sid_tmp<<4)+ch_tmp] = offset_tmp;
    ch_low[(sid_tmp<<4)+ch_tmp] = ch_low_tmp;
    ch_high[(sid_tmp<<4)+ch_tmp] = ch_high_tmp;
  }
  file_par.close();

  //
  file_in = new TFile(TString::Format("%s%s_R%04d.root", RAWFILEPATH, RAWFILENAME, run_number).Data(), "READ");
  if(!file_in->IsOpen())
  {
    std::cout<<"Can't open raw root file"<<std::endl;
    exit(1);
  }
  tr_in = (TTree*)file_in->Get("tree");
  tr_in->SetBranchAddress("sr", &sr);
  tr_in->SetBranchAddress("pileup", &pileup);
  tr_in->SetBranchAddress("outofr", &outofr);
  tr_in->SetBranchAddress("sid", &sid);
  tr_in->SetBranchAddress("ch", &ch);
  tr_in->SetBranchAddress("evte", &evte);
  tr_in->SetBranchAddress("ts", &ts);
  tr_in->SetBranchAddress("cfd", &cfd);
  tr_in->SetBranchAddress("cfdft", &cfdft);
  tr_in->SetBranchAddress("cfds", &cfds);
  total_entry = tr_in->GetEntries();

  file_out = new TFile(TString::Format("%s%s_R%04d_sort.root", ROOTFILEPATH, RAWFILENAME, run_number).Data(), "RECREATE");
  tr_out = new TTree("tr","Pixie16 100M Sort Time Data");
  tr_out->Branch("slot", &ed_value.slot, "slot/S");
  tr_out->Branch("channel", &ed_value.channel, "channel/S");
  tr_out->Branch("energy", &ed_value.energy, "energy/s");
  tr_out->Branch("ts_real", &ed_value.ts_real, "ts_real/L");
  tr_out->Branch("pile_up", &ed_value.pile_up, "pile_up/O");
  tr_out->Branch("out_range", &ed_value.out_range, "out_range/O");
}

TimeSort::~TimeSort()
{
  file_in->cd();
  file_in->Close();
}

//
void TimeSort::Process()
{
  benchmark->Start("TimeSort");

  int id;
  Long64_t ts_now;
  Long64_t delta_time = TIMEBUFF;
  Long64_t size;

  file_in->cd();
  while(true){
    for(Long64_t entry=current_entry;entry<total_entry;++entry){
      tr_in->GetEvent(entry);
      current_entry = entry+1;
      ts_now = ts*10;

      if(ts_now<delta_time){
        ed_value.slot = sid;
        ed_value.channel = ch;
        ed_value.energy = evte;
        ed_value.ts_real = ts*10;
        ed_value.pile_up = pileup;
        ed_value.out_range = outofr;

        id = (sid<<4)+ch;
        if(ed_value.energy<ch_low[id] || ed_value.energy>ch_high[id]){
          continue;
        }

        //alignment
        ed_value.ts_real = ts_now+ts_offset[id];
        key = ((((ed_value.ts_real)<<4)+ed_value.slot)<<4)+ed_value.channel;
        map_sort_data.insert(std::pair<Long64_t, EventData>(key, ed_value));
      }
      else{
        current_entry = entry;
        break;
      }
    }

    std::cout << "\r" << delta_time/1000000000;
    std::cout << std::flush;

    delta_time += TIMEBUFF;
    size = (Long64_t)map_sort_data.size();
    for(Long64_t i=0;i<size;i++){
      it = map_sort_data.begin();
      ed_value = it->second;
      file_out->cd();
      tr_out->Fill();

      map_sort_data.erase(it);
    }

    if(current_entry>=total_entry){
      while(map_sort_data.size()>0){
        it = map_sort_data.begin();
        ed_value = it->second;
        tr_out->Fill();

        map_sort_data.erase(it);
        // std::cout << ">0  " << map_sort_data.size() << std::endl;
      }
    }

    if(current_entry>=total_entry && map_sort_data.size()==0) break;
  }
  

  file_out->cd();
  tr_out->Write();
  file_out->Close();
  
  benchmark->Show("TimeSort");
}