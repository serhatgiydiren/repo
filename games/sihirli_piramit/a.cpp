// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/05/01 14:58:06

#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

class timer:high_resolution_clock
{
 const time_point start_time;
 
 public:
  timer(): start_time(now()) {}
  rep elapsed_time() const { return duration_cast<milliseconds>(now()-start_time).count();} 
};

int time_limit=2000;
timer t;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif
    
mt19937 rng(steady_clock::now().time_since_epoch().count());

void solve(const int &test_id)
{
 int n;
 cin >> n;
 vector < vector < int > > inp(n);
 for(int i=0;i<n;i++)
 {
  inp[i].resize(i+1);
  for(int j=0;j<i+1;j++) cin >> inp[i][j];
 }
 for(auto e:inp) D(e);
 queue < pair < pair < int , int > , vector < int > > > q;
 q.push({{0,0},{inp[0][0]}});
 while(!q.empty())
 {
  auto f=q.front();
  D(f);
  q.pop();

  if (f.first.first==n-1)
  {
   set < int > check;
   for(auto e:f.second) check.insert(e);
   if ((int)check.size()==n)
   {
    D(f.second);
    int p,w,res=0;
    cin >> w;
    while(w--)
    {
     cin >> p;
     res+=f.second[--p];
    }
    D(res);
    exit(0);
   }
   continue;
  }

  for(int k=f.first.second;k<=f.first.second+1;k++)
  {
   auto u=f.second;
   u.push_back(inp[f.first.first+1][k]);
   q.push({{f.first.first+1,k},u});
  }
 }
}

void solve_cases()
{
 int test_cases = 1;
 //cin >> test_cases;
 for(int i = 1; i <= test_cases; i++) { solve(i); D(i,t.elapsed_time()); }
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
