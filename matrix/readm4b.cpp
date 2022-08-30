#include "TCanvas.h"
#include "TPad.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TMath.h"
#include "TRandom.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TSystem.h"

#include <fstream>
#include <iostream>

// m4b file save 4096*4096 array, each data with int/uint size.
int readm4b()
{
  TCanvas *c1 = new TCanvas("c1","",800,800);
  gStyle->SetOptStat(0);
 
  TH2D *h2 = new TH2D("h2","",4096,0,4096,4096,0,4096);
  TH1D *h1;
  
  uint data;

  std::ifstream file_in("combinem4b150to181.m4b", std::ios::binary);

  for(int i=0;i<4096;++i){
    for(int j=0;j<4096;++j){
      file_in.read((char*)&data,sizeof(uint));
      if(data>0){
        h2->Fill(i,j,data);
        for(int k = 0; k < data; ++k){
          h2->Fill(i,j);
        }
      }
    }
  }

  file_in.close();

  h1 = h2->ProjectionX();
  c1->cd();
  
  // h2->Draw("colz");
  h1->Draw("hist");

  cout<<"total = "<<h1->Integral(0,4096)<<endl;
  
  return 0;
}