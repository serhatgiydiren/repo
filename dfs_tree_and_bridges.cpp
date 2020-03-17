// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

struct vertex
{
 int parent;
 vector < int > span_edges;
 vector < int > back_edges;
};

int v,e;
vector < vector < int > > g;
vector < bool > vis;
vector < vertex > dfst;
vector < int > dp_bridge;

void dfs_tree(const int &node, const int &parent=-1)
{
 vis[node]=true;
 dfst[node].parent=parent;
 for(auto ev : g[node])
 {
  cerr << node << " " << ev << endl;
  if (ev==parent) continue;
  if (vis[ev]) dfst[node].back_edges.push_back(ev);
  else
  {
   dfs_tree(ev,node);
   dfst[node].span_edges.push_back(ev);
   dfst[ev].span_edges.push_back(node);
  }
 }
}

void print_dfst()
{
 for(int i=0;i<v;i++)
 {
  cerr << "node=" << i << endl;
  cerr << "span edges = [";
  for(auto ev : dfst[i].span_edges) cerr << ev << " ";
  cerr << "] back edges = [";
  for(auto ev : dfst[i].back_edges) cerr << ev << " ";
  cerr << "]" << endl;
 }
}

int traverse_bridge(const int &node)
{
 if (vis[node]) return dp_bridge[node];
 vis[node]=true;
 cerr << "node=" << node << " dp_bridge[node]=" << dp_bridge[node] << endl;
 for(auto ev : dfst[node].back_edges)
 {
  if (!vis[ev])
  {
   dp_bridge[node]--;
   dp_bridge[ev]++;
  }
 }
 cerr << "after removing down nodes dp_bridge[node]=" << dp_bridge[node] << endl;
 for(auto ev : g[node]) if (!vis[ev]) dp_bridge[node]+=traverse_bridge(ev);
 cerr << "returning for node " << node << " dp_bridge[node]=" << dp_bridge[node] << endl;
 return dp_bridge[node];
}

void find_bridges(const int &root)
{
 dp_bridge.resize(v);
 for(int i=0;i<v;i++) vis[i]=false;
 traverse_bridge(root);
 for(int i=0;i<v;i++)
 {
  cerr << "i=" << i << " dp_bridge[i]=" << dp_bridge[i] << endl;
  if (dp_bridge[i]==0 && dfst[i].parent!=-1) cerr << "bridge = " << i << " " << dfst[i].parent << endl;
 }
}

void solve(const int &test_id)
{
 int u,w;
 cin >> v >> e;
 g.resize(v, vector < int > {});
 vis.resize(v);
 for(int i=0;i<e;i++)
 {
  cin >> u >> w;
  g[--u].push_back(--w);
  g[w].push_back(u);
 }
 dfst.resize(v);
 int root=0;
 dfs_tree(root);
 print_dfst();
 find_bridges(root);
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
