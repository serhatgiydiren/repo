// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

void solve(const int &test_id)
{
 int n,m,a,b,c,d,res=0,tres=0;
 cin >> n >> m;
 map < pair < int , int > , set < pair < int , int > > > mm;
 for(int i=0;i<m;i++)
 {
  cin >> a >> b >> c >> d;
  mm[{a,b}].insert({c,d});
  mm[{c,d}].insert({a,b});
 }
 for(int i=1;i<=n;i++) for(int j=1;j<=n;j++)
 {
  pair < int , int > z={i,j};
  if (mm.find(z)==mm.end()) tres++;
 }
 D(tres);
 D(mm);
 priority_queue < pair < int , pair < int , int > > > pq,sil;
 for(auto e:mm)
 {
  D(e);
  pq.push({e.second.size(),e.first});
  sil.push({e.second.size(),e.first});
 }
 while(!sil.empty())
 {
  D(sil.top());
  sil.pop();
 }
 while(!pq.empty())
 {
  auto f=pq.top();
  D(f);
  D(mm[f.second]);
  pq.pop();
  if (mm[f.second].size()==0) res++;
  /*if (f.first!=(int)mm[f.second].size())
  {
   pq.push({mm[f.second].size(),f.second});
   continue;
  }*/
  for(auto e:mm[f.second])
  {
   D("B ->",e,mm[e]);
   mm[e].erase(f.second);
   D("A ->",e,mm[e]);
  }
 }
 cout << res+tres << endl;
}
            
void solve_cases()
{
 int test_cases=1;
 //cin >> test_cases;
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
