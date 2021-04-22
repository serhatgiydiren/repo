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

void solve(const int &test_id)
{
 int x,y;
 string s;
 cin >> x >> y >> s;
 D(x,y,s);
 int n=s.size();
 vector < vector < int > > dp(n, vector < int > (2, 1000));
 dp[0][0]=dp[0][1]=0;
 for(int i=1;i<n;i++)
 {
  if (s[i]=='C')
  {
   if (s[i-1]=='C') dp[i][0]=dp[i-1][0];
   else if (s[i-1]=='J') dp[i][0]=dp[i-1][1]+y;
   else dp[i][0]=dp[i][1]=min(dp[i-1][0],dp[i-1][1]+y);
   dp[i][1]=dp[i][0];
  }
  else if (s[i]=='J')
  {
   if (s[i-1]=='C') dp[i][1]=dp[i-1][0]+x;
   else if (s[i-1]=='J') dp[i][1]=dp[i-1][1];
   else dp[i][0]=dp[i][1]=min(dp[i-1][0]+x,dp[i-1][1]);
   dp[i][0]=dp[i][1];
  }
  else
  {
   if (s[i-1]=='C')
   {
    dp[i][1]=dp[i-1][0]+x;
    dp[i][0]=dp[i-1][0];
   }
   else if (s[i-1]=='J')
   {
    dp[i][0]=dp[i-1][1]+y;
    dp[i][1]=dp[i-1][1];
   }
   else
   {
    dp[i][0]=min(dp[i-1][0],dp[i-1][1]+y);
    dp[i][1]=min(dp[i-1][1],dp[i-1][0]+x);
   }
  }
  D(i,dp);
 }
 cout << "Case #" << test_id << ": " << min(dp[n-1][0],dp[n-1][1]) << endl;
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

