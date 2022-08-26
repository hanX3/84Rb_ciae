//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Aug 20 16:31:54 2022 by ROOT version 6.24/02
// from TTree tr/Pixie16 100M Sort Time Data
// found on file: ../../../data/data_R0150_sort.root
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
   Short_t         slot;
   Short_t         channel;
   UShort_t        energy;
   Long64_t        ts_real;
   Bool_t          pile_up;
   Bool_t          out_range;

   // List of branches
   TBranch        *b_slot;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_energy;   //!
   TBranch        *b_ts_real;   //!
   TBranch        *b_pile_up;   //!
   TBranch        *b_out_range;   //!

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
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../../../data/data_R0150_sort.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../../../data/data_R0150_sort.root");
      }
      f->GetObject("tr",tree);

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

   fChain->SetBranchAddress("slot", &slot, &b_slot);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("energy", &energy, &b_energy);
   fChain->SetBranchAddress("ts_real", &ts_real, &b_ts_real);
   fChain->SetBranchAddress("pile_up", &pile_up, &b_pile_up);
   fChain->SetBranchAddress("out_range", &out_range, &b_out_range);
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
