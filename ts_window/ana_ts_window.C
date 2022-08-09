#define ana_ts_window_cxx
#include "ana_ts_window.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ana_ts_window::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ana_ts_window.C
//      root> ana_ts_window t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   // hanX3 add
   TH1D *h1 = new TH1D("h1", "h1", 250, -1000, 1000);
   std::vector<Long64_t> vec_ch00;
   std::vector<Long64_t> vec_ch01;

   // get vector
   Long64_t nbytes = 0, nb = 0;
   for(Long64_t jentry=0;jentry<nentries;jentry++) {
   // for(Long64_t jentry=0;jentry<10000000;jentry++) {
      if(jentry%10000000==0){
         cout << jentry << "/" << nentries << endl;
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(sid==3&&ch==2){
         vec_ch00.push_back(ts);
         continue;
      }

      if(sid==3&&ch==3){
         vec_ch01.push_back(ts);
         continue;
      }
   }

   for(int i=0;i<10;i++){
      cout << vec_ch00[i] << " " << vec_ch01[i] << endl;
   }

   int j = 0;
   int k = 0;

   Long64_t ts1, ts2;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch01.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch01.size())  break;
         ts2 = vec_ch01[k];

         if(abs(ts1-ts2)<1000){
            h1->Fill(ts1-ts2);
            k++;
         }
         else if((ts1-ts2)>1000){
            k++;
         }
         else{
            j++;
            break;
         }
      }
   }

   TCanvas *c1 = new TCanvas("c1");
   c1->cd();
   h1->Draw();

   ofstream file_out;
   file_out.open("ts_window.txt");
   for(int i=0;i<h1->GetNbinsX();i++){
      file_out << h1->GetBinCenter(i+1) << " " << h1->GetBinContent(i+1) << endl;
   }
   file_out.close();
}
