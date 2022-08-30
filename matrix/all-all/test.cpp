
void test()
{
  long long a[10];
  for(int i=0;i<10;i++){
    cout << a[i] << endl;
  }

  memset(a, 0, sizeof(long long)*10);
  for(int i=0;i<10;i++){
    cout << a[i] << endl;
  }
}