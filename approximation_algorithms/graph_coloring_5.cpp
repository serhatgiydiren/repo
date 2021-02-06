#include <bits/stdc++.h>

using namespace std;
 
struct vertex
{
 int id;
 int color;
 vector < int > adj;
};
int v,e,cc=-1,lb;
vector < vertex > vert;
vector < int > idx_map,cc_list,shuffled_color_list;
unsigned shuffle_index=0;

bool vertex_sorter(vertex v1, vertex v2)
{
 return (v1.adj.size()>v2.adj.size() || (v1.adj.size()==v2.adj.size() && v1.id<v2.id));
}

bool is_feasible(const int &idx, const int &cid)
{
 for(unsigned i=0;i<vert[idx].adj.size();i++) if (vert[ idx_map[ vert[idx].adj[i] ] ].color==cid) return false;
 return true;
}

void set_cc_list()
{
 cc_list.clear();
 for(int q=0;q<v;q++) if (vert[q].color==cc) cc_list.push_back(q);
}

bool set_color(const int &idx, const int &cid)
{
 if (idx==v) return true;
 if (!is_feasible(idx,cid)) return false;
 vert[idx].color=cid;
 if (cid>cc) cc=cid;
 for(int i=0;i<max(lb,cc+2);i++) if (set_color(idx+1,i)) return true;
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

void print_color_list()
{
 for(int i=0;i<v;i++) cerr << vert[i].color << " ";
 cerr << endl;
}

int any_feasible_color(const int &q,const int &current_color)
{
 for(int i=0;i<cc;i++,shuffle_index++)
 {
  int c=(shuffle_index+i)%cc;
  if (shuffled_color_list[c]!=current_color && is_feasible(q,shuffled_color_list[c])) return shuffled_color_list[c];
 }
 return -1;
}

void process_feasible_pair(const int &q)
{
 int prev_color=vert[q].color;
 for(int i=0;i<cc;i++,shuffle_index++)
 {
  int c=(shuffle_index+i)%cc;
  if (c==prev_color) continue;
  //cerr << "test color=" << i << endl;
  vert[q].color=c;
  vector < pair < int , int > > backups;
  bool status=true;
  for(unsigned j=0;j<vert[q].adj.size();j++)
  {
   int neigh=idx_map[vert[q].adj[j]];
   if (vert[neigh].color==c)
   {
    //cerr << "same color neigh=" << neigh << endl;
    int new_color=any_feasible_color(neigh,vert[neigh].color);
    if (new_color!=-1)
    {
     //cerr << "j=" << j << " new_color=" << new_color << endl;
     backups.push_back(make_pair(neigh,vert[neigh].color));
     vert[neigh].color=new_color;
    }
    else
    {
     status=false;
     for(unsigned k=0;k<backups.size();k++) vert[backups[k].first].color=backups[k].second;
     break;
    }
   }
  }
  if (status)
  {
   //cerr << "q=" << q << " prev_color=" << prev_color << " new color 2=" << c << endl;
   return;
  }
 }
 vert[q].color=prev_color;
 return;
}

void set_shuffled_color_list()
{
 shuffled_color_list.resize(cc);
 for(int i=0;i<cc;i++) shuffled_color_list[i]=i;
 random_shuffle(shuffled_color_list.begin(),shuffled_color_list.end());
}

void do_better_2(const int &z)
{
 int q=rand()%vert[z].adj.size();
 int idx=idx_map[vert[z].adj[q]];
 int new_color=any_feasible_color(idx,vert[idx].color);
 if (new_color!=-1) vert[idx].color=new_color;
 else process_feasible_pair(idx);
}

void do_better_1()
{
 int new_color;
 bool found=false;
 for(unsigned i=0;i<cc_list.size();i++)
 {
  int q=cc_list[i];
  if (vert[q].color==cc)
  {
   found=true;
   /*new_color=any_feasible_color(q,vert[q].color);
   if (new_color!=-1)
   {
    //cerr << "q=" << q << " new color 1=" << new_color << endl;
    cc_list.erase(cc_list.begin()+i);
    i--;
    vert[q].color=new_color;
   }
   else */process_feasible_pair(q);
  }
  if (vert[q].color==cc) do_better_2(q);
 }
 if (!found)
 {
  cc--;
  set_shuffled_color_list();
  set_cc_list();
  cerr << "new cc=" << cc << endl;
 }
}

void do_better()
{
 set_shuffled_color_list();
 set_cc_list();
 int check=100000;
 while(check--)
 {
  if(check%10000==0) cerr << "check point=" << check << " cc=" << cc << endl;
  do_better_1();
  do_better_2(rand()%v);
 }
}

void print_output()
{
 cout << cc+1 << " " << 0 << endl;
 for(int i=0;i<v;i++) cout << vert[ idx_map[i] ].color << " ";
 cout << endl;
}

void welsh_powell()
{
 lb=0;
 vector < bool > seen(v);
 for(int i=0;i<v;i++)
 {
  if (seen[i]) continue;
  seen[i]=true;
  vector < bool > not_connected(v,true);
  for(unsigned j=0;j<vert[i].adj.size();j++) not_connected[ idx_map[ vert[i].adj[j] ] ]=false;
  for(int j=0;j<v;j++) if (not_connected[j]) seen[j]=true;
  lb++;
 }
 cerr << "welsh_powell lower_bound=" << lb << endl;
}

void solve() {
 srand(time(NULL));
 int u,w;
 cin >> v >> e;
 vert.resize(v);
 for(int i=0;i<v;i++) vert[i].id=i,vert[i].color=-1;
 idx_map.resize(v);
 for(int i=0;i<e;i++)
 {
  cin >> u >> w;
  vert[u].adj.push_back(w);
  vert[w].adj.push_back(u);
 }
 sort(vert.begin(),vert.end(),vertex_sorter);
 for(int i=0;i<v;i++) idx_map[ vert[i].id ]=i;
 welsh_powell();
 if (set_color(0,0))
 {
  print_color_list();
  do_better();
  print_color_list();
  print_output();
 }
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
