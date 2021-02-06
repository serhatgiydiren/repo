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
 int id;
 loc lc;
};

vector < vertex > vert,best;

double dist(int a, int b)
{
 a=(a+n)%n;
 b=(b+n)%n;
 return sqrt(pow(vert[a].lc.x-vert[b].lc.x,2)+pow(vert[a].lc.y-vert[b].lc.y,2));
}

void set_tot_distance()
{
 tot_dist=0; 
 for(int i=0;i<n;i++) tot_dist+=dist(i,i+1);
 best_dist=tot_dist;
}

bool is_accepted(const double &diff, const double &temperature)
{
 //cerr << diff << " " << diff/temperature << " " << exp(diff/temperature) << endl;
 if (diff>EPS) return true;
 if (exp(diff/temperature)-0.99>EPS) return true;
 return false;
}

void simulated_annealing()
{
 double temperature=1000;
 int idx_1,idx_2;
 double diff;
 while(temperature>EPS)
 {
  idx_1=rand()%n;
  idx_2=rand()%n;
  if (idx_1==idx_2) continue;
  if (idx_1>idx_2) swap(idx_1,idx_2);
  if (idx_2-idx_1==1) diff=dist(idx_1,idx_1-1)+dist(idx_2,idx_2+1)-( dist(idx_2,idx_1-1)+dist(idx_1,idx_2+1) );
  else if (idx_2-idx_1==n-1) diff=dist(idx_1,idx_1+1)+dist(idx_2,idx_2-1)-( dist(idx_2,idx_1+1)+dist(idx_1,idx_2-1) );
  else diff=dist(idx_1,idx_1-1)+dist(idx_1,idx_1+1)+dist(idx_2,idx_2-1)+dist(idx_2,idx_2+1)-(dist(idx_2,idx_1-1)+dist(idx_2,idx_1+1)+dist(idx_1,idx_2-1)+dist(idx_1,idx_2+1));
  if (is_accepted(diff,temperature))
  {
   swap(vert[idx_1],vert[idx_2]);
   tot_dist-=diff;
   if (tot_dist<best_dist)
   {
    best_dist=tot_dist;
    best=vert;
    cerr << idx_1 << " " << idx_2 << " " << diff << " " << best_dist << " temperature=" << temperature << endl;
   }
  }
  temperature-=0.0001;
 }
}

void print_output()
{
 cout << best_dist << " " << 0 << endl;
 for(int i=0;i<n;i++) cout << best[i].id << " ";
 cout << endl;
}

void solve() {
 srand(time(NULL));
 cout << fixed << setprecision(4);
 cerr << fixed << setprecision(4);
 cin >> n;
 assert(n>1);
 vert.resize(n);
 for(int i=0;i<n;i++)
 {
  cin >> vert[i].lc.x >> vert[i].lc.y;
  vert[i].id=i;
 }
 random_shuffle(vert.begin(),vert.end());
 set_tot_distance();
 simulated_annealing();
 print_output();
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
