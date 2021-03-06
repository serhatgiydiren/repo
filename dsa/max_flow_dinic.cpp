// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

struct FlowEdge
{
 int v, u, cap, flow = 0;
 FlowEdge(int _v, int _u, int _cap) : v(_v), u(_u), cap(_cap) {}
};

struct Dinic
{
 const int flow_inf = 1e9;
 vector < FlowEdge > edges;
 vector< vector < int > > adj;
 int n, m = 0;
 int s, t;
 vector < int > level, ptr;
 queue < int > q;

 Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t)
 {
  adj.resize(n);
  level.resize(n);
  ptr.resize(n);
 }

 void add_edge(int v, int u, int cap)
 {
  edges.emplace_back(v, u, cap);
  edges.emplace_back(u, v, 0);
  adj[v].push_back(m);
  adj[u].push_back(m + 1);
  m += 2;
 }

 bool bfs()
 {
  while (!q.empty())
  {
   int v = q.front();
   q.pop();
   for (int id : adj[v])
   {
    if (edges[id].cap - edges[id].flow < 1) continue;
    if (level[edges[id].u] != -1) continue;
    level[edges[id].u] = level[v] + 1;
    q.push(edges[id].u);
   }
  }
  return level[t] != -1;
 }

 int dfs(int v, int pushed)
 {
  if (pushed == 0) return 0;
  if (v == t) return pushed;
  for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++)
  {
   int id = adj[v][cid];
   int u = edges[id].u;
   if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) continue;
   int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
   if (tr == 0) continue;
   edges[id].flow += tr;
   edges[id ^ 1].flow -= tr;
   return tr;
  }
  return 0;
 }

 int flow()
 {
  int f = 0;
  while (true)
  {
   fill(level.begin(), level.end(), -1);
   level[s] = 0;
   q.push(s);
   if (!bfs()) break;
   fill(ptr.begin(), ptr.end(), 0);
   while (int pushed = dfs(s, flow_inf)) f += pushed;
  }
  return f;
 }
};

void solve(const int &test_id)
{
 int V,E;
 int v,u,cap;
 cin >> V >> E;
 Dinic d(V,0,V-1);
 for (int i=0;i<E;i++)
 {
  cin >> v >> u >> cap;
  d.add_edge(--v,--u,cap);
 }
 cout << d.flow() << endl;
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
