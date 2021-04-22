// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/03/26 16:21:30

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

int ut(const int &n, vector < int > &x)
{
 int res=0;
 for(int i=0;i<n-1;i++)
 {
  int z=min_element(x.begin()+i,x.end())-x.begin();
  res+=(z+1-i);
  reverse(x.begin()+i,x.begin()+z+1);
 }
 return res;
}

void solve(const int &test_id)
{
 int a,b;
 cin >> a >> b;
 cout << "Case #" << test_id << ": ";
 if (b<a-1 || b>(a*(a+1))/2-1) cout << "IMPOSSIBLE" << endl;
 else
 {
  b-=(a-1);
  vector < int > res(a);
  int left=0,right=a-1,z=a-1,cur=1,q=1,loc=-1;
  while(b)
  {
   if (b>=z)
   {
    if (q==1) loc=right--;
    else loc=left++;
   }
   else
   {
    if (q==1) loc=right-(z-b);
    else loc=left+(z-b);
   }
   res[loc]=cur++;
   b-=min(b,z--);
   q=1-q;
  }
  if (loc==-1 && q==0) loc=a;
  if (q==0)
  {
   for(int i=loc-1;i>=left;i--) res[i]=cur++;
   for(int i=loc+1;i<=right;i++) res[i]=cur++;
  }
  else
  {
   for(int i=loc+1;i<=right;i++) res[i]=cur++;
   for(int i=loc-1;i>=left;i--) res[i]=cur++;
  }
  for(auto e:res) cout << e << " ";
  cout << endl;
 }
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

