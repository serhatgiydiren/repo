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
vector < string > table;

void read_process(vector < vector < vector < int > > > &_cand,
                  const int &idx)
{
 vector < int > temp(n);
 temp.back()=1;
 do
 {
  _cand[idx].push_back(temp);
 } while(next_permutation(temp.begin(),temp.end()));
}

vector < int > dx={1,1,-1,-1,0,0,1,-1};
vector < int > dy={1,-1,1,-1,1,-1,0,0};

void ut(const int &idx=0, vector < vector < int > > ch={})
{
 if (idx==n)
 {
  for(int i=0;i<n;i++)
  {
   for(int j=0;j<n;j++)
   {
    if (ch[i][j]==0) continue;
    for(int k=0;k<4;k++)
    {
     int ii=i+dx[k];
     int jj=j+dy[k];
     if (ii>=0 && ii<n && jj>=0 && jj<n && ch[ii][jj]==1) return;
    }
   }
  }
  map < char , int > zone;
  for(int j=0;j<n;j++)
  {
   int c=0;
   for(int i=0;i<n;i++)
   {
    if (ch[i][j]==1)
    {
     if (++c>1) return;
     if (++zone[table[i][j]]>1) return;
    }
   }
  }
  for(auto e:ch) D(e);
  exit(0);
 }
 for(auto e:row_cand[idx])
 {
  auto ch_next=ch;
  ch_next.push_back(e);
  ut(idx+1,ch_next);
 }
}

void solve(const int &test_id)
{
 cin >> n;
 row_cand.resize(n);
 col_cand.resize(n);
 table.resize(n);
 for(auto &e:table) cin >> e;
 for(int i=0;i<n;i++) read_process(row_cand,i);
 for(int i=0;i<n;i++) read_process(col_cand,i);
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
