// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int a,b,n;
 string res;
 cin >> a >> b >> n;
 int lo=a+1;
 int hi=b;
 while(lo<hi)
 {
  int mid=(lo+hi)>>1;
  cout << mid << flush << endl;
  cin >> res;
  if (res=="CORRECT") return;
  else if (res=="TOO_BIG") hi=mid-1;
  else if (res=="TOO_SMALL") lo=mid+1;
  else assert(0==1);
 }
 cout << hi << flush << endl;
 cin >> res;
 assert(res=="CORRECT");
}
            
void solve_cases()
{
 int test_cases=1;
 cin >> test_cases;
 for(int i=1;i<=test_cases;i++) solve(i);
}

void fast_io()
{
 ios::sync_with_stdio(false);
 srand(time(NULL));
 cin.tie(0);
 cout.tie(0);
 cout << fixed << setprecision(15);
 cerr << fixed << setprecision(15);
}

int main()
{
 fast_io();
 solve_cases();
 return EXIT_SUCCESS;
}
