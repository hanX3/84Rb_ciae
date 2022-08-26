// #define FILENAME "../ts_window/ts_window.root"
#define FILENAME "../ts_window_check/ts_window.root"

//
void get_data_ts_window()
{
  TFile *file_in = TFile::Open(TString::Format("%s",FILENAME).Data());

  THStack *hs = new THStack("hs", "Stacked 1D histograms");

  TH1D *h_ch00_ch01 = (TH1D*)file_in->Get("h_ch00_ch01");
  TH1D *h_ch00_ch02 = (TH1D*)file_in->Get("h_ch00_ch02");
  TH1D *h_ch00_ch03 = (TH1D*)file_in->Get("h_ch00_ch03");
  TH1D *h_ch00_ch04 = (TH1D*)file_in->Get("h_ch00_ch04");
  TH1D *h_ch00_ch05 = (TH1D*)file_in->Get("h_ch00_ch05");
  
  TH1D *h_ch00_ch08 = (TH1D*)file_in->Get("h_ch00_ch08");
  TH1D *h_ch00_ch09 = (TH1D*)file_in->Get("h_ch00_ch09");
  TH1D *h_ch00_ch10 = (TH1D*)file_in->Get("h_ch00_ch10");

  hs->Add(h_ch00_ch01);
  hs->Add(h_ch00_ch02);
  hs->Add(h_ch00_ch03);
  hs->Add(h_ch00_ch04);

  hs->Draw();

  ofstream file_out;
  file_out.open("ts_check.txt");

  for(int i=0;i<h_ch00_ch01->GetNbinsX();i++){
    file_out << h_ch00_ch01->GetBinCenter(i+1) << " " << h_ch00_ch01->GetBinContent(i+1) << " " << h_ch00_ch02->GetBinContent(i+1) << " " << h_ch00_ch05->GetBinContent(i+1) <<endl;
  }

  file_out.close();
}