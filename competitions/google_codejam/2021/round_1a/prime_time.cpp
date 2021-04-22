// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/04/22 23:04:17

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

vector < pair < int , long long > > x;

bool check(long long prod, int sum)
{
 for(auto e:x)
 {
  int cnt=0;
  while(prod%e.first==0)
  {
   prod/=e.first;
   sum-=e.first;
   cnt++;
  }
  if (cnt>e.second) return false;
 }
 return (prod==1 && sum==0);
}

void solve(const int &test_id)
{
 int n;
 cin >> n;
 long long s=0,res=0;
 x.resize(n);
 for(auto &e:x) cin >> e.first >> e.second,s+=(e.first*e.second);
 for(int i=1;res==0 && i<min(s,(long long)30000);i++) if (check(s-i,i)) res=s-i;
 cout << "Case #" << test_id << ": " << res << endl;
}

void solve_cases()
{
 int test_cases = 1;
 cin >> test_cases;
 for(int i = 1; i <= test_cases; i++) solve(i);
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
