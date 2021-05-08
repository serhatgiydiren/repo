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
vector < vector < int > > perms;
int sil=0;

void set_cand(const int &idx=0, vector < vector < int > > ch={})
{
 for(int j=0;j<idx;j++)
 {
  set < int > check;
  for(int i=0;i<idx;i++) check.insert(ch[i][j]);
  if ((int)check.size()!=idx) return;
 }
 
 for(auto e:perms)
 {
  if (idx==0)
  {
   if (e[2]<e[3]) continue;   
  }
  else if (idx==1)
  {
   if (e[3]<e[4]) continue;
   if (e[0]<ch[idx-1][0]) continue;
   if (e[2]<ch[idx-1][2]) continue;
  }
  else if (idx==2)
  {
   if (e[2]<e[3]) continue;
   if (e[0]<ch[idx-1][0]) continue;
   if (e[1]<ch[idx-1][1]) continue;
   if (e[2]<ch[idx-1][2]) continue;
   if (e[4]>ch[idx-1][4]) continue;
  }
  else if (idx==3)
  {
   if (e[2]<e[3]) continue;
   if (e[2]<ch[idx-1][2]) continue;
   if (e[3]>ch[idx-1][3]) continue;
  }
  else if (idx==4)
  {
   if (e[3]>e[4]) continue;
   if (e[1]>ch[idx-1][1]) continue;
  }

  if (idx==n)
  {
   for(auto f:ch) D(f);
   return;
  }

  auto ch_next=ch;
  ch_next.push_back(e);
  set_cand(idx+1,ch_next);
 }
}

void set_perms()
{
 vector < int > temp(n);
 iota(temp.begin(),temp.end(),1);
 do
 {
  perms.push_back(temp);
 } while(next_permutation(temp.begin(),temp.end()));
}

void solve(const int &test_id)
{
 cin >> n;
 set_perms();
 set_cand();
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
