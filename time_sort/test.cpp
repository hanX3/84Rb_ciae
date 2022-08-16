
void test()
{
  Long64_t a = 100;
  cout << a<<4 << endl;

  map<Long64_t, Int_t> map_m;
  map_m.insert(pair<Long64_t, Int_t>(10, 1));
  map_m.insert(pair<Long64_t, Int_t>(20, 3));
  map_m.insert(pair<Long64_t, Int_t>(0, 5));

  map<Long64_t, Int_t>::iterator it;
  for(it=map_m.begin();it!=map_m.end();it++){
    cout << it->first << " " << it->second << endl;
  }

  //
  map_m.insert(pair<Long64_t, Int_t>(20, 7));
  for(it=map_m.begin();it!=map_m.end();it++){
    cout << it->first << " " << it->second << endl;
  }

}