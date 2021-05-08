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

int time_limit=100000;
timer t;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif
    
mt19937 rng(steady_clock::now().time_since_epoch().count());

int n,oc=0;
vector < string > inp;
vector < vector < int > > adj;
vector < int > dx={1,-1,0,0};
vector < int > dy={0,0,1,-1};

int max_path_length=0;
vector < int > best_path;

void print(const vector < int > &path)
{
 D(path);
 auto res=inp;
 auto raw=path;
 for(int i=1;i<oc-1;i++)
 {
  if (raw[i]==raw[i-1]+n && raw[i]+n==raw[i+1]) res[raw[i]/n][raw[i]%n]='|';
  else if (raw[i]==raw[i-1]-n && raw[i]-n==raw[i+1]) res[raw[i]/n][raw[i]%n]='|';

  else if (raw[i]==raw[i-1]+1 && raw[i]+1==raw[i+1]) res[raw[i]/n][raw[i]%n]='-';
  else if (raw[i]==raw[i-1]-1 && raw[i]-1==raw[i+1]) res[raw[i]/n][raw[i]%n]='-';

  else if (raw[i]==raw[i-1]+n && raw[i]+1==raw[i+1]) res[raw[i]/n][raw[i]%n]='L';
  else if (raw[i]==raw[i-1]-1 && raw[i]-n==raw[i+1]) res[raw[i]/n][raw[i]%n]='L';

  else if (raw[i]==raw[i-1]+1 && raw[i]+n==raw[i+1]) res[raw[i]/n][raw[i]%n]='q';
  else if (raw[i]==raw[i-1]-n && raw[i]-1==raw[i+1]) res[raw[i]/n][raw[i]%n]='q';

  else if (raw[i]==raw[i-1]+n && raw[i]-1==raw[i+1]) res[raw[i]/n][raw[i]%n]='j';
  else if (raw[i]==raw[i-1]+1 && raw[i]-n==raw[i+1]) res[raw[i]/n][raw[i]%n]='j';

  else if (raw[i]==raw[i-1]-1 && raw[i]+n==raw[i+1]) res[raw[i]/n][raw[i]%n]='p';
  else if (raw[i]==raw[i-1]-n && raw[i]+1==raw[i+1]) res[raw[i]/n][raw[i]%n]='p';
 }
 for(auto e:res) D(e);
}

bool check(const vector < int > &path, const set < int > &path_unique)
{
 for(int i=0;i<n;i++)
 {
  for(int j=0;j<n;j++)
  {
   if (inp[i][j]=='0') continue;
   if (path_unique.find(i*n+j)!=path_unique.end()) continue;
   int fr=0;

   for(int k=0;k<4;k++)
   {
    int new_i=i+dx[k];
    int new_j=j+dy[k];
    if (new_i>=0 && new_i<n && new_j>=0 && new_j<n && inp[new_i][new_j]=='1')
    {
     if (path_unique.find(new_i*n+new_j)==path_unique.end() || path.back()==(new_i*n+new_j)) fr++;
    }
   }
   
   if (fr==0) return false;
  }
 }
 return true;
}

void dfs(const int &idx, const vector < int > &path, const set < int > &path_unique)
{
 if (int(path.size())>max_path_length)
 {
  max_path_length=int(path.size());
  best_path=path;
  D(max_path_length,t.elapsed_time());
 }
 if ((int)path.size()==oc)
 {
  D("found");
  print(path);
  exit(0);
 }
  
 if (t.elapsed_time()>time_limit)
 {
  D("expires");
  print(best_path);
  exit(0);
 }
  
 for(auto e:adj[idx])
 {
  if (path_unique.find(e)==path_unique.end())
  {
   auto w=path;
   auto v=path_unique;
   w.push_back(e);
   v.insert(e);
   if (check(w,v)) dfs(e,w,v);
  }
 }
}

void solve(const int &test_id)
{
 cin >> n;
 inp.resize(n);
 adj.resize(n*n);
 for(auto &e:inp) cin >> e;
 for(int i=0;i<n;i++)
 {
  for(int j=0;j<n;j++)
  {
   if (inp[i][j]=='0') continue;
   oc++;
   for(int k=0;k<4;k++)
   {
    int new_i=i+dx[k];
    int new_j=j+dy[k];
    if (new_i>=0 && new_i<n && new_j>=0 && new_j<n && inp[new_i][new_j]=='1')
    {
     adj[i*n+j].push_back(new_i*n+new_j);
    }
   }
  }
 }
 D(oc);
 D(adj);
 dfs(0,{0},{0});
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
