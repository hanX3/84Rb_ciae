
//sid=2 is the bgo slot
//sid=3 is the hpge slot

void get_his_raw(int runno)
{
  char filename[256];

  sprintf(filename, "../../data/data_R%04d.root", runno);
  cout << "start ana " << filename << endl;

  TFile *fi;
  TTree *tr;
  fi = TFile::Open(filename);

  TH1D *h_raw[2][16];
  char tr_name[256];

  stringstream ss1, ss2, ss3;
  ss1.str("");
  ss2.str("");
  ss3.str("");

  tr = (TTree*)fi->Get("tree");

  for(int i=0;i<2;i++){
    for(int j=0;j<16;j++){
      ss1.str("");
      ss1 << "h_raw_mod" << i << "_ch" << j;
      cout << ss1.str() << endl;
      h_raw[i][j] = new TH1D(ss1.str().c_str(), ss1.str().c_str(), 65536, 0, 65536);

      ss2.str("");
      ss2 << "evte>>h_raw_mod" << i << "_ch" << j;
      cout << ss2.str() << endl;

      ss3.str("");
      ss3 << "sid==" << i+2 << "&&ch==" << j;
      cout << ss3.str() << endl;

      tr->Draw(ss2.str().c_str(), ss3.str().c_str());
    }
  }


  TDirectory *dir_mod[2];

  sprintf(filename, "./run%04d_raw_spe.root", runno);
  TFile *fo = new TFile(filename, "recreate");

  for(int i=0;i<2;i++){
    fo->cd();
    ss1.str("");
    ss1 << "mod" << i;
    dir_mod[i] = fo->mkdir(ss1.str().c_str());
    dir_mod[i]->cd();
    for(int j=0;j<16;j++){
      h_raw[i][j]->Write();
    }
  }

  fo->Close();
}
