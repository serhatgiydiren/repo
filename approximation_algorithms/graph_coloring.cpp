#include <bits/stdc++.h>
 
using namespace std;
 
struct vertex
{
 int id;
 int color;
 vector < int > adj;
};

int v,e,cc,max_idx,max_color,prev_max_color;

vector < vertex > vert;

vector < int > idx_map;

bool vertex_sorter(vertex v1, vertex v2)
{
 return (v1.adj.size()>v2.adj.size() || (v1.adj.size()==v2.adj.size() && v1.id<v2.id));
}

bool set_color(int idx, int cid)
{
 if (idx>max_idx)
 {
  cerr << "idx=" << idx << endl;
  max_idx=idx;
 }
 int prev_color=vert[idx].color;
 for(unsigned i=0;i<vert[idx].adj.size();i++)
 {
  if (vert[idx_map[vert[idx].adj[i]]].color==cid) return false;
 }
 vert[idx].color=cid;
 if (idx==v-1) return true;
 prev_max_color=max_color;
 max_color=max(max_color,cid);
 for(int i=0;i<cc;i++)
 {
  bool res=set_color(idx+1,i);
  if (res) return true;
  else if (i>max_color) break;
 }
 max_color=prev_max_color;
 vert[idx].color=prev_color;
 return false;
}

void solve() {
 int u,w;
 cin >> v >> e;
 vert.resize(v);
 idx_map.resize(v);
 for(int i=0;i<v;i++) vert[i].id=i;
 for(int i=0;i<e;i++)
 {
  cin >> u >> w;
  vert[u].adj.push_back(w);
  vert[w].adj.push_back(u);
 }
 sort(vert.begin(),vert.end(),vertex_sorter);
 for(int i=0;i<v;i++) idx_map[vert[i].id]=i;
 for(int i=0;i<v;i++)
 {
  cerr << vert[i].id << " " << vert[i].adj.size() << "->";
  for(unsigned idx=0;idx<vert[i].adj.size();idx++) cerr << vert[i].adj[idx] << " ";
  cerr << endl;
 }

 for(cc=1;cc<=vert[0].adj.size()+1;cc++)
 {
  cerr << "trying " << cc << "..." << endl;
  max_idx=-1;
  max_color=0;
  for(int i=0;i<v;i++) vert[i].color=-1;
  if (set_color(0,0))
  {
   cout << cc << " " << 0 << endl;
   for(int i=0;i<v;i++) cout << vert[idx_map[i]].color << " ";
   cout << endl;
   break;
  }
 }
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
