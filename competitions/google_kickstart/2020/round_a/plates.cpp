// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,e,k;
 cin >> n >> e >> k;
 vector < vector < int > > dp(n+1, vector < int > (k+1));
 vector < vector < int > > x(n, vector < int > (e+1));
 for(int i=0;i<n;i++) for(int j=1;j<e+1;j++) cin >> x[i][j],x[i][j]+=x[i][j-1];
 for(int i=1;i<n+1;i++) for(int j=1;j<k+1;j++) for(int w=0;w<min(j+1,e+1);w++)
  dp[i][j]=max(dp[i-1][j-w]+x[i-1][w],dp[i][j]);
 cout << "Case #" << test_id << ": " << dp[n][k] << endl;
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
