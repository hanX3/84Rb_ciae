
void get_data(int run, int ch)
{
  TFile *file_in = TFile::Open(TString::Format("../../data/data_R%04d.root",run).Data());
  if(file_in->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TTree *tr = (TTree*)file_in->Get("tree");
  TH1D *h = new TH1D("h", "", 65536, 0,65536);

  stringstream ss;
  ss.str("");
  ss << "sid==" << 3 << "&&ch==" << ch;

  tr->Draw("evte>>h", ss.str().c_str());

  ofstream file_out;
  file_out.open(TString::Format("run%04d_ch%02d.txt",run,ch).Data());
  for(int i=0;i<h->GetNbinsX();i++){
    file_out << i+1 << " " << h->GetBinContent(i+1) << endl;
  }
  file_out.close();
}