#define ts_diff_cxx
#include "ts_diff.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void ts_diff::Loop()
{
//   In a ROOT session, you can do:
//      root> .L ts_diff.C
//      root> ts_diff t
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

   Long64_t nbytes = 0, nb = 0;

   // hanX add
   TH1D *hh = new TH1D("hh", "", 200, -1000, 1000);

   Double_t ts_pre, ts_diff;
   // for (Long64_t jentry=0; jentry<nentries;jentry++) {
   for (Long64_t jentry=0; jentry<1000000;jentry++) {
      if(jentry%1000000==0)  cout << jentry << "/" << nentries << endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      if(jentry==0){
         ts_pre = ts;
         continue;
      }

      ts_diff = 10.*(ts-ts_pre);
      hh->Fill(ts_diff);

      ts_pre = ts;
   }

   hh->Draw();
}
