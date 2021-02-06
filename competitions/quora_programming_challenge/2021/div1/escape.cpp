// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

struct guard
{
 int r,c,d;
};

struct point
{
 int x,y;
};

int n,m,k;

vector < point > dirs={{-1,0},{1,0},{0,1},{0,-1}};

vector < guard > g;
vector < vector < bool > > vis;
vector < string > maze;
vector < vector < int > > p;

void bfs(int gid)
{
 queue < pair < point , int > > q;
 q.push({{g[gid].r,g[gid].c},0});
 p[g[gid].r][g[gid].c]=max(p[g[gid].r][g[gid].c],g[gid].d);
 vis[g[gid].r][g[gid].c]=true;
 while(!q.empty())
 {
  auto f=q.front();
  //D(f.first.x,f.first.y,f.second);
  q.pop();
  if (g[gid].d-f.second<p[f.first.x][f.first.y]) continue;
  for(auto e:dirs)
  {
   auto new_x=f.first.x+e.x;
   auto new_y=f.first.y+e.y;
   if (new_x>=0 && new_x<n && new_y>=0 && new_y<m && maze[new_x][new_y]!='#' && !vis[new_x][new_y] && f.second<g[gid].d)
   {
    vis[new_x][new_y]=true;
    p[new_x][new_y]=max(p[new_x][new_y],g[gid].d-f.second-1);
    if (f.second+1<g[gid].d) q.push({{new_x,new_y},f.second+1});
   }
  }
 }
}

bool sort_g(guard g1,guard g2)
{
 return g1.d>g2.d;
}

void solve(const int &test_id)
{
 int res=INT_MAX;
 point start={0,0},end={0,0};
 cin >> n >> m >> k;
 vis.assign(n, vector < bool > (m));
 p.assign(n, vector < int > (m, 0));
 maze.resize(n);
 for(int i=0;i<n;i++)
 {
  cin >> maze[i];
  for(int j=0;j<m;j++)
  {
   if (maze[i][j]=='S') start={i,j};
   else if (maze[i][j]=='E') end={i,j};
  }
 }
 g.resize(k);
 for(int i=0;i<k;i++)
 {
  cin >> g[i].r >> g[i].c >> g[i].d;
  g[i].r--;
  g[i].c--;
 }
 sort(g.begin(),g.end(),sort_g);
 for(int i=0;i<k;i++) bfs(i);
 if (!vis[start.x][start.y] && !vis[end.x][end.y])
 {
  queue < pair < point , int > > q;
  q.push({start,0});
  vis[start.x][start.y]=true;
  while(!q.empty())
  {
   auto f=q.front();
   q.pop();
   if (f.first.x==end.x && f.first.y==end.y) res=min(res,f.second);
   for(auto e:dirs)
   {
    auto new_x=f.first.x+e.x;
    auto new_y=f.first.y+e.y;
    if (new_x>=0 && new_x<n && new_y>=0 && new_y<m && maze[new_x][new_y]!='#' && !vis[new_x][new_y])
    {
     vis[new_x][new_y]=true;
     q.push({{new_x,new_y},f.second+1});
    }
   }
  }
 }
 if (res==INT_MAX) cout << "IMPOSSIBLE" << endl;
 else cout << res << endl;
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
