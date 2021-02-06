#include <bits/stdc++.h>

using namespace std;
 
struct vertex
{
 int id;
 int color;
 vector < int > adj;
};

int v,e,cc,max_idx=-1,timeout;
unsigned curr_idx=0;
clock_t t1;
vector < vertex > vert;

vector < int > idx_map,color_shuffle;

bool vertex_sorter(vertex v1, vertex v2)
{
 return (v1.adj.size()>v2.adj.size() || (v1.adj.size()==v2.adj.size() && v1.id<v2.id));
}

bool is_feasible(const int &idx, const int &cid)
{
 for(unsigned i=0;i<vert[idx].adj.size();i++) if (vert[ idx_map[ vert[idx].adj[i] ] ].color==cid) return false;
 return true;
}

bool set_color(const int &idx, const int &cid)
{
 if (idx>max_idx)
 {
  max_idx=idx;
  cerr << idx << " " << cid << " " << clock()-t1 << endl;
 }
 if (idx==v) return true;
 if (clock()-t1>timeout) return false;
 if (!is_feasible(idx,cid)) return false;
 vert[idx].color=cid;
 unsigned local_idx=curr_idx;
 for(int i=0;i<cc;i++,curr_idx++) if (set_color(idx+1,color_shuffle[(local_idx+i)%cc])) return true;
 vert[idx].color=-1;
 return false;
}

void print_vert()
{
 for(int i=0;i<v;i++)
 {
  cerr << vert[i].id << " " << vert[i].adj.size() << "->";
  for(unsigned idx=0;idx<vert[i].adj.size();idx++) cerr << vert[i].adj[idx] << " ";
  cerr << endl;
 }
}

void solve() {
 srand(time(NULL));
 int u,w;
 cin >> v >> e;
 
 vert.resize(v);
 for(int i=0;i<v;i++) vert[i].id=i;
 idx_map.resize(v);
 for(int i=0;i<e;i++)
 {
  cin >> u >> w;
  vert[u].adj.push_back(w);
  vert[w].adj.push_back(u);
 }
 sort(vert.begin(),vert.end(),vertex_sorter);
 for(int i=0;i<v;i++) idx_map[ vert[i].id ]=i;

 for(cc=1;cc<v;cc++)
 {
  cerr << "trying " << cc << endl;

  color_shuffle.resize(cc);
  for(int i=0;i<cc;i++) color_shuffle[i]=i;
  random_shuffle(color_shuffle.begin(),color_shuffle.end());
  for(int i=0;i<cc;i++) cerr << color_shuffle[i] << " "; cerr << endl;

  for(int i=0;i<v;i++) vert[i].color=-1;

  t1=clock();
  timeout=500000000;

  if (set_color(0,0))
  {
   cout << cc << " " << 0 << endl;
   for(int i=0;i<v;i++) cout << vert[ idx_map[i] ].color << " "; cout << endl;
   break;
  }
 }
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
