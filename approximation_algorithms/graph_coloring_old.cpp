// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>
 
using namespace std;
 
struct vertex
{
 int id;
 int color;
 vector < int > adj;
};

int v,e,cc,max_idx;

vector < vertex > vert;

vector < int > idx_map;

bool vertex_sorter(vertex v1, vertex v2)
{
 return (v1.adj.size()>v2.adj.size() || (v1.adj.size()==v2.adj.size() && v1.id<v2.id));
}

bool set_color(int idx, int cid, int max_color)
{
 if (idx<4) cerr << "idx=" << idx << " cid=" << cid << " max_color=" << max_color << endl;
 if (idx>max_idx)
 {
  cerr << "idx=" << idx << endl;
  max_idx=idx;
 }
 int prev_color=vert[idx].color;
 for(unsigned i=0;i<vert[idx].adj.size();i++)
 {
  if (vert[idx_map[vert[idx].adj[i]]].color==cid)
  {
   //cout << "returning false 1..." << endl;
   return false;
  }
 }
 vert[idx].color=cid;
 if (idx==v-1)
 {
  //cout << "returning true 1..." << endl;
  return true;
 }
 if (cid>max_color)
 {
  max_color=cid;
  cerr << "max_color=" << max_color << endl;
 }
 for(int i=0;i<cc;i++)
 {
  bool res=set_color(idx+1,i,max_color+1);
  if (res)
  {
   //cout << "returning true 2..." << endl;
   return true;
  }
  else if (i>max_color) break;
 }
 vert[idx].color=prev_color;
 //cout << "returning false 2..." << endl;
 return false;
}

int welsh_powell()
{
 int res=0;
 vector < bool > seen(v);
 //for(int i=0;i<v;i++) cerr << vert[i].id << " "; cerr << endl;
 for(int i=0;i<v;i++)
 {
  if (seen[i]) continue;
  //cerr << i << " " << vert[i].id << "->";
  seen[i]=true;
  vector < bool > not_connected(v,true);
  for(unsigned j=0;j<vert[i].adj.size();j++) not_connected[idx_map[vert[i].adj[j]]]=false;
  for(int j=0;j<v;j++) if (not_connected[j]) seen[j]=true;
  //for(int j=0;j<v;j++) cerr << seen[j] << " "; cerr << endl;
  res++;
 }
 return res;
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
 int lower_bound=welsh_powell();
 lower_bound=18;
 for(cc=lower_bound;cc<=(int)vert[0].adj.size()+1;cc++)
 {
  cerr << "trying " << cc << "..." << endl;
  max_idx=-1;
  for(int i=0;i<v;i++) vert[i].color=-1;
  if (set_color(0,0,0))
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
