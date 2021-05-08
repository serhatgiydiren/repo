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

int n;
vector < vector < vector < int > > > row_cand,col_cand;
vector < int > val_r,val_c;

void ut(const int &idx=0, vector < vector < int > > ch={})
{
 for(int j=0;j<n;j++)
 {
  int q=1,w=0;
  for(int i=0;i<idx;i++) if (ch[i][j]) w++,q*=ch[i][j];
  if (w>2) return;
  if (q>val_c[j]) return;
 }

 if (idx==n)
 {
  set < int > b;
  for(int j=0;j<n;j++)
  {
   for(int i=0;i<n;i++) if (ch[i][j]) b.insert(ch[i][j]);
  }
  if ((int)b.size()!=2*n) return;
  for(auto e:ch) D(e);
  exit(0);
 }
 vector < int > x(n,0);
 for(int i=1;i<=2*n;i++) for(int j=1;j<=2*n;j++)
 {
  if (i==j) continue;
  if (i*j==val_r[idx])
  {
   x[n-2]=i;
   x[n-1]=j;
   do
   {
    auto ch_new=ch;
    ch_new.push_back(x);
    ut(idx+1,ch_new);
   } while(next_permutation(x.begin(),x.end()));
  }
 } 
}

void solve(const int &test_id)
{
 cin >> n;
 row_cand.resize(n);
 col_cand.resize(n);
 val_r.resize(n);
 val_c.resize(n);
 for(auto &e:val_r) cin >> e;
 for(auto &e:val_c) cin >> e;
 ut();
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
