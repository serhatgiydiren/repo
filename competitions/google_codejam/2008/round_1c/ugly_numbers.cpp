// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

const int A=40;
const int B=2;
const int M=210;
long long dp[A][B][M][B][M];

void solve(const int &test_id)
{
 memset(dp,0ll,sizeof(dp));
 long long res=0;
 string s;
 cin >> s;
 dp[0][0][s[0]-'0'][0][0]++;
 for(size_t i=1;i<s.size();i++)
 {
  for(int bc=0;bc<B;bc++) for(int c=0;c<M;c++) for(int bd=0;bd<B;bd++) for(int d=0;d<M;d++)
   if (dp[i-1][bc][c][bd][d])
   {
    dp[i][bc][(10*c+(s[i]-'0'))%M][bd][d]+=dp[i-1][bc][c][bd][d];
    int r=((1-2*bc)*c+(1-2*bd)*d)%M;
    int zr=0;
    if (r<0) zr=1,r=-r;
    dp[i][0][s[i]-'0'][zr][r]+=dp[i-1][bc][c][bd][d];
    dp[i][1][s[i]-'0'][zr][r]+=dp[i-1][bc][c][bd][d];
   }
 }
 for(int bc=0;bc<B;bc++) for(int c=0;c<M;c++) for(int bd=0;bd<B;bd++) for(int d=0;d<M;d++)
  if (dp[s.size()-1][bc][c][bd][d])
  {
   int w=(1-2*bc)*c+(1-2*bd)*d;
   if (w%2==0 || w%3==0 || w%5==0 || w%7==0) res+=dp[s.size()-1][bc][c][bd][d];
  }
 cout << "Case #" << test_id << ": " << res << endl;
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
