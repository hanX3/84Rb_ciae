#include "set.h"
#include "Sort.h"

#include "TBranch.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>

//
Sort::Sort(TString raw, TString out, TString name, int number)
{
  nevt = 0;
  run_no = number;

  benchmark = new TBenchmark;
  ran = new TRandom(0);

  for(int i=0;i<Crate0num;++i){
    for(int j=0;j<16;j++){
      cali_par0[i][j] = 0;
      cali_par1[i][j] = 0;
      cali_par2[i][j] = 0;
    }
  }

  event_flag = false;
  memset(event_slot, 0, sizeof(int)*100);
  memset(event_channel, 0, sizeof(int)*100);
  memset(event_energy, 0, sizeof(double)*100);
  memset(event_ts, 0, sizeof(long long)*100);

  //
  sprintf(temp_file_name, "%s%s_R%04d_sort.root", raw.Data(), name.Data(), run_no);
  file_in = new TFile(temp_file_name, "READ");
  if(!file_in->IsOpen())
  {
    std::cout << "Can't open raw root file" << std::endl;
    exit(1);
  }

  tr_in = (TTree*)file_in->Get("tr");
  tr_in->SetBranchAddress("slot", &slot);
  tr_in->SetBranchAddress("channel", &channel);
  tr_in->SetBranchAddress("energy", &energy);
  tr_in->SetBranchAddress("ts_real", &ts_real);
  tr_in->SetBranchAddress("pile_up", &pile_up);
  tr_in->SetBranchAddress("out_range", &out_range);
  
  total_entry = tr_in->GetEntries();
  tr_in->Print();
  std::cout << "total_entry: " << total_entry << std::endl;

  sprintf(temp_file_name, "%s%s_R%04d_m%d_all_90.root", out.Data(), name.Data(), run_no, WINDOWS);
  file_out = new TFile(temp_file_name, "RECREATE");

  matrix = new TH2I("matrix", "CIAE in beam gamma matrix", 4096, BIN_MIN, BIN_MAX, 4096, BIN_MIN, BIN_MAX);
}

//
Sort::~Sort()
{

}

//
void Sort::ClearOpt()
{
  hit_num = 0;

  memset(event_slot, 0, sizeof(int)*100);
  memset(event_channel, 0, sizeof(int)*100);
  memset(event_energy, 0, sizeof(double)*100);
  memset(event_ts, 0, sizeof(long long)*100);
}

//
bool Sort::GetCalPar()
{
  sprintf(temp_file_name, "../../cali/inbeam_cali_par/%04d.txt", run_no);
  std::ifstream file_cal(temp_file_name, std::ifstream::in);
  if(!file_cal){
    std::cout  << "cannot find cali file" << std::endl;
    return false;
  }
  std::cout << "read cali file " << std::endl;

  int ch = 0;
  double chi2 = 0;
  for(int i=0;i<Crate0num;++i){
    for(int j=0;j<16;++j) {
      if(!FLAGCHANNEL[i][j])  continue;
      file_cal >> ch >> chi2 >> cali_par0[i][j] >> cali_par1[i][j] >> cali_par2[i][j];
    }
  }

  for(int i=0;i<Crate0num;++i){
    for(int j=0; j<16; ++j){
      std::cout << cali_par0[i][j] << "  " << cali_par1[i][j] << "  " << cali_par2[i][j] << std::endl;
    }
  }

  file_cal.close();
  return true;
}

//
void Sort::Process()
{
  benchmark->Start("event");

  for(Long64_t entry=0;entry<total_entry;++entry){
    if(entry%10000 == 0){
      std::cout << "\r" << "Entry: " << entry <<"  |  Event: " << nevt+1;
      std::cout << std::flush;
    }
    file_in->cd();
    // tr_in->Show(entry);
    tr_in->GetEntry(entry);

    if(event_flag){
      ts_now = ts_real;
      if(TMath::Abs(ts_now-ts_init) <= Long64_t(WINDOWS)){
        ProcessEntry();
      }
      else{
        FillMatrix();
        InitEvent();
      }
    }
    else{
      InitEvent();
      event_flag = true;
    }
  }

  std::cout << std::endl;
  
  // write matrix file
  FILE *fp;
  sprintf(temp_file_name, "run%04d_m%d_all_90.m4b", run_no, WINDOWS);
  if((fp=fopen(temp_file_name,"ab")) == NULL){
    std::cout<<"can't open file .m4b"<<std::endl;
  }

  int count;
  for(int i=1;i<=4096;++i){
    for(int j=1;j<=4096;++j){
      count = int(matrix->GetBinContent(i, j));
      fwrite(&count,sizeof(int),1,fp);
    }
  }

  fclose(fp);

  file_in->cd();
  file_in->Close();

  file_out->cd();
  matrix->Write();

  file_out->Close();

  benchmark->Show("event");
}

//
void Sort::InitEvent()
{
  ClearOpt();
  ts_init = ts_real;

  ProcessEntry();
}

//
void Sort::ProcessEntry()
{
  temp_energy = energy + ran->Rndm();
  temp_energy = cali_par0[slot-3][channel] + temp_energy*cali_par1[slot-3][channel] + temp_energy*temp_energy*cali_par2[slot-3][channel];
  if(temp_energy<THRE_LOW || temp_energy>THRE_HIGH){
    return;
  }

  event_slot[hit_num] = slot;
  event_channel[hit_num] = channel;
  event_energy[hit_num] = temp_energy;
  event_ts[hit_num] = ts_real;
  hit_num++;
}

//
void Sort::FillMatrix()
{
  if(hit_num<2){
    return;
  }

  bool event_90_flag = false;
  for(int i=0;i<hit_num;i++){
    if(!MMDETCHANNEL[event_channel[i]]) continue;
    else{
      event_90_flag = true;
    }
  }
  
  if(!event_90_flag) return;

  //
  nevt++;
  for(int i=0;i<hit_num;++i){
    for(int j=0;j<hit_num;++j){
      if(i==j) continue;
      if(MMDETCHANNEL[event_channel[i]]){
        matrix->Fill(event_energy[j], event_energy[i]);
      }
      else{
        if(MMDETCHANNEL[event_channel[j]]){
          matrix->Fill(event_energy[i], event_energy[j]);
        }
        else continue;
      }
    }
  }
}