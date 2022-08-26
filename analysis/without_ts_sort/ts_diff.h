//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Aug 20 16:13:42 2022 by ROOT version 6.24/02
// from TTree tree/PKU XIA Pixie-16 Data
// found on file: ../../../data/data_R0150.root
//////////////////////////////////////////////////////////

#ifndef ts_diff_h
#define ts_diff_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ts_diff {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Short_t         sr;
   Bool_t          pileup;
   Bool_t          outofr;
   Short_t         cid;
   Short_t         sid;
   Short_t         ch;
   UShort_t        evte;
   Long64_t        ts;
   Long64_t        ets;
   Short_t         cfd;
   Bool_t          cfdft;
   Short_t         cfds;
   UInt_t          trae;
   UInt_t          leae;
   UInt_t          gape;
   Double_t        base;
   UInt_t          qs[8];
   UShort_t        ltra;
   UShort_t        data[1];   //[ltra]
   UShort_t        dt[1];   //[ltra]
   Int_t           nevt;

   // List of branches
   TBranch        *b_sr;   //!
   TBranch        *b_pileup;   //!
   TBranch        *b_outofr;   //!
   TBranch        *b_cid;   //!
   TBranch        *b_sid;   //!
   TBranch        *b_ch;   //!
   TBranch        *b_evte;   //!
   TBranch        *b_ts;   //!
   TBranch        *b_ets;   //!
   TBranch        *b_cfd;   //!
   TBranch        *b_cfdft;   //!
   TBranch        *b_cfds;   //!
   TBranch        *b_trae;   //!
   TBranch        *b_leae;   //!
   TBranch        *b_gape;   //!
   TBranch        *b_base;   //!
   TBranch        *b_qs;   //!
   TBranch        *b_ltra;   //!
   TBranch        *b_data;   //!
   TBranch        *b_dt;   //!
   TBranch        *b_nevt;   //!

   ts_diff(TTree *tree=0);
   virtual ~ts_diff();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ts_diff_cxx
ts_diff::ts_diff(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../../data/data_R0150.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../../data/data_R0150.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

ts_diff::~ts_diff()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ts_diff::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ts_diff::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ts_diff::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("sr", &sr, &b_sr);
   fChain->SetBranchAddress("pileup", &pileup, &b_pileup);
   fChain->SetBranchAddress("outofr", &outofr, &b_outofr);
   fChain->SetBranchAddress("cid", &cid, &b_cid);
   fChain->SetBranchAddress("sid", &sid, &b_sid);
   fChain->SetBranchAddress("ch", &ch, &b_ch);
   fChain->SetBranchAddress("evte", &evte, &b_evte);
   fChain->SetBranchAddress("ts", &ts, &b_ts);
   fChain->SetBranchAddress("ets", &ets, &b_ets);
   fChain->SetBranchAddress("cfd", &cfd, &b_cfd);
   fChain->SetBranchAddress("cfdft", &cfdft, &b_cfdft);
   fChain->SetBranchAddress("cfds", &cfds, &b_cfds);
   fChain->SetBranchAddress("trae", &trae, &b_trae);
   fChain->SetBranchAddress("leae", &leae, &b_leae);
   fChain->SetBranchAddress("gape", &gape, &b_gape);
   fChain->SetBranchAddress("base", &base, &b_base);
   fChain->SetBranchAddress("qs", qs, &b_qs);
   fChain->SetBranchAddress("ltra", &ltra, &b_ltra);
   fChain->SetBranchAddress("data", &data, &b_data);
   fChain->SetBranchAddress("dt", &dt, &b_dt);
   fChain->SetBranchAddress("nevt", &nevt, &b_nevt);
   Notify();
}

Bool_t ts_diff::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ts_diff::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ts_diff::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ts_diff_cxx
