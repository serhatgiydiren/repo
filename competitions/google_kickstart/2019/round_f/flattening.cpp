// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

const int N=105;
const int M=1005;

int removal[N][N];
int dp[N][N];

int f(const int &n, const int &k)
{
 if (k==0) return removal[0][n];
 if (dp[n][k]!=-1) return dp[n][k];
 int res=INT_MAX;
 for(int i=0;i<=n;i++) res=min(res,f(i,k-1)+removal[i+1][n]);
 return dp[n][k]=res;
}

void solve(const int &test_id)
{
 int n,k;
 cin >> n >> k;
 vector < int > x(n);
 for(auto &e:x) cin >> e;
 memset(removal,0,sizeof(removal));
 memset(dp,-1,sizeof(dp));
 for(int i=0;i<n;i++) for(int j=i;j<n;j++)
 {
  vector < int > c(M);
  for(int u=i;u<=j;u++) c[x[u]]++;
  removal[i][j]=(j-i+1)-*max_element(c.begin(),c.end());
 }
 cout << "Case #" << test_id << ": " << f(n-1,k) << endl;
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
