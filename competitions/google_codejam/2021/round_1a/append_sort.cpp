// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/04/10 03:58:18

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

string inc(string s)
{
 int c=1;
 for(int i=(int)s.size()-1;i>=0;i--)
 {
  int t=(s[i]-'0')+c;
  c=0;
  if (t>9) t=0,c=1;
  s[i]=('0'+t);
 }
 if (c) s.insert(s.begin(),'1');
 return s;
}

void solve(const int &test_id)
{
 int n,res=0;
 string p="0",q;
 cin >> n;
 while(n--)
 {
  cin >> q;
  while (q.size()<p.size() || (q.size()==p.size() && q<p))
  {
   if (q==p.substr(0,q.size())) q+=p[q.size()];
   else q+='0';
   res++;
  }
  p=inc(q);
 }
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

