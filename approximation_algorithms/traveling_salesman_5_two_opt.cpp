// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>
 
using namespace std;

#define EPS 1e-9

int n;
double tot_dist,best_dist=DBL_MAX;

struct loc
{
 double x;
 double y;
};
 
struct vertex
{
 loc lc;
 int next_vert_id;
};

vector < vertex > vert,best;

double dist(const int &a,const int &b)
{
 return sqrt(pow(vert[a].lc.x-vert[b].lc.x,2)+pow(vert[a].lc.y-vert[b].lc.y,2));
}

int nx(const int &a)
{
 return vert[a].next_vert_id;
}

void set_tot_distance()
{
 tot_dist=0; 
 for(int i=0;i<n;i++) tot_dist+=dist(i,nx(i));
 best_dist=tot_dist;
 best=vert;
}

void simulated_annealing()
{
 long long log_freq=10000000;
 int not_changed=0;
 long long iteration=100*log_freq;
 while(iteration--)
 {
  if (iteration%log_freq==0) cerr << "iter=" << iteration << " tot_dist=" << tot_dist << " best_dist=" << best_dist << endl;
  int ix_1=rand()%n;
  int ix_2=rand()%n;
  if (ix_1==ix_2) continue;
  int ix_1_next=nx(ix_1);
  int ix_2_next=nx(ix_2);
  if (ix_1==ix_2_next || ix_2==ix_1_next) continue;
  double diff=dist(ix_1,ix_1_next)+dist(ix_2,ix_2_next)-dist(ix_1,ix_2)-dist(ix_1_next,ix_2_next);

  if (diff>EPS || not_changed>10000)
  {
   not_changed=0;
   int left=ix_1_next;
   int backup=nx(ix_1_next);
   while(left!=ix_2)
   {
    int backup_next=nx(backup);
    vert[backup].next_vert_id=left;
    left=backup;
    backup=backup_next;
   }
   vert[ix_1].next_vert_id=ix_2;
   vert[ix_1_next].next_vert_id=ix_2_next;

   tot_dist-=diff;
   if (tot_dist<best_dist)
   {
    best_dist=tot_dist;
    best=vert;
   }
  }
  else not_changed++;
 }
}

void print_output()
{
 cout << best_dist << " " << 0 << endl;
 cout << 0 << " ";
 int q=best[0].next_vert_id;
 while(q)
 {
  cout << q << " ";
  q=best[q].next_vert_id;
 }
 cout << endl;
}

void solve() {
 srand(time(NULL));
 cout << fixed << setprecision(4);
 cerr << fixed << setprecision(4);
 cin >> n;
 vert.resize(n);
 for(int i=0;i<n;i++)
 {
  cin >> vert[i].lc.x >> vert[i].lc.y;
  vert[i].next_vert_id=-1;
 }

 vector < bool > seen(n);
 int q=0;
 for(int i=0;i<n;i++)
 {
  seen[q]=true;
  double best_pair_dist=DBL_MAX;
  int best_ix=0;
  for(int j=0;j<n;j++)
  {
   if (seen[j]) continue;
   double temp_dist=dist(q,j);
   if (temp_dist<best_pair_dist)
   {
    best_ix=j;
    best_pair_dist=temp_dist;
   }
  }
  q=vert[q].next_vert_id=best_ix;
 }

 set_tot_distance();
 cerr << "init=" << best_dist << endl;
 simulated_annealing();
 print_output();
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
