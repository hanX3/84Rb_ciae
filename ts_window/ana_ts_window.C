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
   TH1D *h_ch00_ch01 = new TH1D("h_ch00_ch01", "", 250, -1000, 1000);
   TH1D *h_ch00_ch02 = new TH1D("h_ch00_ch02", "", 250, -1000, 1000);
   TH1D *h_ch00_ch03 = new TH1D("h_ch00_ch03", "", 250, -1000, 1000);
   TH1D *h_ch00_ch04 = new TH1D("h_ch00_ch04", "", 250, -1000, 1000);
   TH1D *h_ch00_ch05 = new TH1D("h_ch00_ch05", "", 250, -1000, 1000);
   TH1D *h_ch00_ch06 = new TH1D("h_ch00_ch06", "", 250, -1000, 1000);
   TH1D *h_ch00_ch07 = new TH1D("h_ch00_ch07", "", 250, -1000, 1000);
   TH1D *h_ch00_ch08 = new TH1D("h_ch00_ch08", "", 250, -1000, 1000);
   TH1D *h_ch00_ch09 = new TH1D("h_ch00_ch09", "", 250, -1000, 1000);
   TH1D *h_ch00_ch10 = new TH1D("h_ch00_ch10", "", 250, -1000, 1000);
   TH1D *h_ch00_ch11 = new TH1D("h_ch00_ch11", "", 250, -1000, 1000);
   TH1D *h_ch00_ch12 = new TH1D("h_ch00_ch12", "", 250, -1000, 1000);
   TH1D *h_ch00_ch13 = new TH1D("h_ch00_ch13", "", 250, -1000, 1000);
   TH1D *h_ch00_ch14 = new TH1D("h_ch00_ch14", "", 250, -1000, 1000);
   TH1D *h_ch00_ch15 = new TH1D("h_ch00_ch15", "", 250, -1000, 1000);

   std::vector<Long64_t> vec_ch00;
   std::vector<Long64_t> vec_ch01;
   std::vector<Long64_t> vec_ch02;
   std::vector<Long64_t> vec_ch03;
   std::vector<Long64_t> vec_ch04;
   std::vector<Long64_t> vec_ch05;
   std::vector<Long64_t> vec_ch06;
   std::vector<Long64_t> vec_ch07;
   std::vector<Long64_t> vec_ch08;
   std::vector<Long64_t> vec_ch09;
   std::vector<Long64_t> vec_ch10;
   std::vector<Long64_t> vec_ch11;
   std::vector<Long64_t> vec_ch12;
   std::vector<Long64_t> vec_ch13;
   std::vector<Long64_t> vec_ch14;
   std::vector<Long64_t> vec_ch15;

   // get vector
   Long64_t nbytes = 0, nb = 0;
   for(Long64_t jentry=0;jentry<nentries;jentry++) {
      if(jentry%10000000==0){
         cout << jentry << "/" << nentries << endl;
      }
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(sid==3&&ch==0){
         vec_ch00.push_back(ts);
         continue;
      }
      if(sid==3&&ch==1){
         vec_ch01.push_back(ts);
         continue;
      }
      if(sid==3&&ch==2){
         vec_ch02.push_back(ts);
         continue;
      }
      if(sid==3&&ch==3){
         vec_ch03.push_back(ts);
         continue;
      }
      if(sid==3&&ch==4){
         vec_ch04.push_back(ts);
         continue;
      }
      if(sid==3&&ch==5){
         vec_ch05.push_back(ts);
         continue;
      }
      if(sid==3&&ch==6){
         vec_ch06.push_back(ts);
         continue;
      }
      if(sid==3&&ch==7){
         vec_ch07.push_back(ts);
         continue;
      }
      if(sid==3&&ch==8){
         vec_ch08.push_back(ts);
         continue;
      }
      if(sid==3&&ch==9){
         vec_ch09.push_back(ts);
         continue;
      }
      if(sid==3&&ch==10){
         vec_ch10.push_back(ts);
         continue;
      }
      if(sid==3&&ch==11){
         vec_ch11.push_back(ts);
         continue;
      }
      if(sid==3&&ch==12){
         vec_ch12.push_back(ts);
         continue;
      }
      if(sid==3&&ch==13){
         vec_ch13.push_back(ts);
         continue;
      }
      if(sid==3&&ch==14){
         vec_ch14.push_back(ts);
         continue;
      }
      if(sid==3&&ch==15){
         vec_ch15.push_back(ts);
         continue;
      }
   }

   int j = 0;
   int k = 0;
   Long64_t ts1, ts2;

   //h_ch00_ch01
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch01.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch01.size())  break;
         ts2 = vec_ch01[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch01->Fill(ts1-ts2);
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

   //h_ch00_ch02
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch02.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch02.size())  break;
         ts2 = vec_ch02[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch02->Fill(ts1-ts2);
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

   //h_ch00_ch03
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch03.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch03.size())  break;
         ts2 = vec_ch03[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch03->Fill(ts1-ts2);
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

   //h_ch00_ch04
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch04.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch04.size())  break;
         ts2 = vec_ch04[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch04->Fill(ts1-ts2);
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

   //h_ch00_ch05
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch05.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch05.size())  break;
         ts2 = vec_ch05[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch05->Fill(ts1-ts2);
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

   //h_ch00_ch06
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch06.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch06.size())  break;
         ts2 = vec_ch06[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch06->Fill(ts1-ts2);
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

   //h_ch00_ch07
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch07.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch07.size())  break;
         ts2 = vec_ch07[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch07->Fill(ts1-ts2);
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

   //h_ch00_ch08
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch08.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch08.size())  break;
         ts2 = vec_ch08[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch08->Fill(ts1-ts2);
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

   //h_ch00_ch09
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch09.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch09.size())  break;
         ts2 = vec_ch09[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch09->Fill(ts1-ts2);
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

   //h_ch00_ch10
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch10.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch10.size())  break;
         ts2 = vec_ch10[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch10->Fill(ts1-ts2);
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

   //h_ch00_ch11
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch11.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch11.size())  break;
         ts2 = vec_ch11[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch11->Fill(ts1-ts2);
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

   //h_ch00_ch12
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch12.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch12.size())  break;
         ts2 = vec_ch12[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch12->Fill(ts1-ts2);
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

   //h_ch00_ch13
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch13.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch13.size())  break;
         ts2 = vec_ch13[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch13->Fill(ts1-ts2);
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

   //h_ch00_ch14
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch14.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch14.size())  break;
         ts2 = vec_ch14[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch14->Fill(ts1-ts2);
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

   //h_ch00_ch15
   j = 0;
   k = 0;
   while(true){
      if(j==(Long64_t)vec_ch00.size() || k==(Long64_t)vec_ch15.size())  break; 
      
      ts1 = vec_ch00[j];
      while(true){
         if(k==(Long64_t)vec_ch15.size())  break;
         ts2 = vec_ch15[k];

         if(abs(ts1-ts2)<1000){
            h_ch00_ch15->Fill(ts1-ts2);
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

   //
   TFile *file_out = new TFile("ts_window.root", "recreate");
   file_out->cd();
   h_ch00_ch01->Write();
   h_ch00_ch02->Write();
   h_ch00_ch03->Write();
   h_ch00_ch04->Write();
   h_ch00_ch05->Write();
   h_ch00_ch06->Write();
   h_ch00_ch07->Write();
   h_ch00_ch08->Write();
   h_ch00_ch09->Write();
   h_ch00_ch10->Write();
   h_ch00_ch11->Write();
   h_ch00_ch12->Write();
   h_ch00_ch13->Write();
   h_ch00_ch14->Write();
   h_ch00_ch15->Write();
   file_out->Close();

   // ofstream file_out;
   // file_out.open("ts_window.txt");
   // for(int i=0;i<h_ch00_ch15->GetNbinsX();i++){
   //    file_out << h_ch00_ch15->GetBinCenter(i+1) << " " << h1->GetBinContent(i+1) << endl;
   // }
   // file_out.close();
}
