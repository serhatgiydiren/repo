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
vector < vector < int > > rows,cols;
vector < int > row_c,col_c;

vector < int > parse(vector < int > temp)
{
 vector < int > z;
 int c=0;
 for(auto e:temp)
 {
  if (e==1) c++;
  else
  {
   if (c) z.push_back(c);
   c=0;
  }
 }
 if (c) z.push_back(c);
 return z;
}

bool check(vector < int > temp, vector < int > orig)
{
 return (parse(temp)==orig);
}

void read_process(vector < vector < int > > &_main, 
                  vector < int > &_c,
                  vector < vector < vector < int > > > &_cand,
                  const int &idx)
{
 int c;
 cin >> c;
 _main[idx].resize(c);
 for(auto &e:_main[idx]) cin >> e,_c[idx]+=e;

 vector < int > temp(n);
 for(int j=n-_c[idx];j<n;j++) temp[j]=1;
 do
 {
  if (check(temp,_main[idx])) _cand[idx].push_back(temp);
 } while(next_permutation(temp.begin(),temp.end()));
}

void ut(const int &idx=0, vector < vector < int > > ch={})
{
 vector < vector < int > > counts(n);
 for(int i=0;i<n;i++)
 {
  vector < int > temp(n);
  for(int j=0;j<idx;j++) temp[j]=ch[j][i];
  counts[i]=parse(temp);
  if (counts[i].size()>cols[i].size()) return;
  for(unsigned k=0;k<min(counts[i].size(),cols[i].size());k++) if (counts[i][k]>cols[i][k]) return;
 }

 if (idx==n)
 {
  if (counts==cols)
  {
   string res="";
   for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
    {
     cout << ch[i][j];
     if (i==j)
     {
      if (ch[i][j]) res+="D";
      else res+="B";
     }
    }
    cout << endl;
   }
   D(res);
   exit(0);
  }
  return;
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
 rows.resize(n);
 cols.resize(n);
 row_cand.resize(n);
 col_cand.resize(n);
 row_c.resize(n);
 col_c.resize(n);
 for(int i=0;i<n;i++) read_process(rows,row_c,row_cand,i);
 for(int i=0;i<n;i++) read_process(cols,col_c,col_cand,i);
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
