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
vector < int > ll,rr,bb,tt;
vector < set < vector < int > > > row_cand,col_cand;

void ut(const int &idx=0, vector < vector < int > > ch={})
{
 if (idx==n)
 {
  for(int j=0;j<n;j++)
  {
   vector < int > check;
   for(int i=0;i<n;i++) check.push_back(ch[i][j]);
   if (col_cand[j].find(check)==col_cand[j].end()) return;
  }
  for(auto e:ch) D(e);
  return;
 }

 for(int j=0;j<idx;j++)
 {
  set < int > check;
  for(int i=0;i<idx;i++) check.insert(ch[i][j]);
  if ((int)check.size()!=idx) return;
 }
 
 for(auto e:row_cand[idx])
 {
  auto ch_next=ch;
  ch_next.push_back(e);
  ut(idx+1,ch_next);
 }
}

int val(vector < int > temp)
{
 int c=1;
 int mv=temp[0];
 for(int i=1;i<n;i++)
 {
  if (temp[i]>mv)
  {
   c++;
   mv=temp[i];
  }
 }
 return c;
}

void set_cand()
{
 vector < int > temp(n);
 for(int i=0;i<n;i++)
 {
  iota(temp.begin(),temp.end(),1);
  do
  {
   if (ll[i] && val(temp)!=ll[i]) continue;
   auto temp_rev=temp;
   reverse(temp_rev.begin(),temp_rev.end());
   if (rr[i] && val(temp_rev)!=rr[i]) continue;
   row_cand[i].insert(temp);
  } while(next_permutation(temp.begin(),temp.end()));
 }
 for(int i=0;i<n;i++)
 {
  iota(temp.begin(),temp.end(),1);
  do
  {
   if (tt[i] && val(temp)!=tt[i]) continue;
   auto temp_rev=temp;
   reverse(temp_rev.begin(),temp_rev.end());
   if (bb[i] && val(temp_rev)!=bb[i]) continue;
   col_cand[i].insert(temp);
  } while(next_permutation(temp.begin(),temp.end()));
 }
}

void solve(const int &test_id)
{
 cin >> n;
 ll.resize(n);
 bb.resize(n);
 rr.resize(n);
 tt.resize(n);
 row_cand.resize(n);
 col_cand.resize(n);
 for(auto &e:ll) cin >> e;
 for(auto &e:bb) cin >> e;
 for(auto &e:rr) cin >> e;
 for(auto &e:tt) cin >> e;
 set_cand();
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
