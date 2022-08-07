
void analysis()
{
  //R0012
  TFile *file_in_r0012 = TFile::Open("../../data/data_R0012.root");
  if(file_in_r0012->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TH1D *h_r0012 = new TH1D("h_r0012", "", 65536, 0,65536);
  TTree *tr_r0012 = (TTree*)file_in_r0012->Get("tree");
  tr_r0012->Draw("evte>>h_r0012", "ch==0");

  //R0020
  TFile *file_in_r0020 = TFile::Open("../../data/data_R0020.root");
  if(file_in_r0020->IsZombie()){
    cout << "wrong open the file" << endl;
    return;
  }

  TH1D *h_r0020 = new TH1D("h_r0020", "", 65536, 0,65536);
  TTree *tr_r0020 = (TTree*)file_in_r0020->Get("tree");
  tr_r0020->Draw("evte>>h_r0020", "ch==0");


  double sum_r0012 = h_r0012->GetEntries();
  double sum_r0020 = h_r0020->GetEntries();

  cout << sum_r0012 << endl;
  cout << sum_r0020 << endl;

  h_r0020->Scale(7235/6668.);

  h_r0012->SetLineColor(4);
  h_r0020->SetLineColor(2);



  h_r0012->Draw();
  h_r0020->Draw("same hist");

  //get data
  ofstream file_out_r0012;
  file_out_r0012.open("r0012.txt");
  for(int i=0;i<h_r0012->GetNbinsX();i++){
    file_out_r0012 << i+1 << " " << h_r0012->GetBinContent(i+1) << endl;
  }
  file_out_r0012.close();

  ofstream file_out_r0020;
  file_out_r0020.open("r0020.txt");
  for(int i=0;i<h_r0020->GetNbinsX();i++){
    file_out_r0020 << i+1 << " " << h_r0020->GetBinContent(i+1) << endl;
  }
  file_out_r0020.close();
}