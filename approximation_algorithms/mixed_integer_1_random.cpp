// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>
 
using namespace std;

#define EPS 1e-9

int n,m;
double tot_cost,best_cost=DBL_MAX;

struct loc
{
 double x;
 double y;
};
 
struct warehouse
{
 double cost;
 int served;
 double cap_cur;
 loc lc;
};
 
struct customer
{
 int demand;
 int w_id;
 loc lc;
};

vector < warehouse > w;
vector < customer > c,best;

double dist(const loc &lc1, const loc &lc2)
{
 return sqrt(pow(lc1.x-lc2.x,2)+pow(lc1.y-lc2.y,2));
}

void set_tot_distance()
{
 tot_cost=0; 
 for(int i=0;i<n;i++) if (w[i].served) tot_cost+=w[i].cost;
 for(int i=0;i<m;i++) tot_cost+=dist(c[i].lc,w[c[i].w_id].lc);
 best_cost=tot_cost;
 best=c;
}

void simulated_annealing()
{
 long long log_freq=1e6;
 long long iteration=1e2*log_freq;
 while(iteration--)
 {
  if (iteration%log_freq==0) cerr << "iter=" << iteration << " cur=" << tot_cost << " best=" << best_cost << endl;
  int c_id=rand()%m;
  int w_id=rand()%n;
  if (w_id==c[c_id].w_id) continue;
  if (w[w_id].cap_cur<c[c_id].demand) continue;
  double diff=0;
  if (w[c[c_id].w_id].served==1) diff+=w[c[c_id].w_id].cost;
  if (w[w_id].served==0) diff-=w[w_id].cost;
  diff+=dist(c[c_id].lc,w[c[c_id].w_id].lc);
  diff-=dist(c[c_id].lc,w[w_id].lc);
  //cerr << "c_id=" << c_id << " w_id=" << w_id << " diff=" << diff << endl;
  if (diff>EPS)
  {
   tot_cost-=diff;
   w[c[c_id].w_id].served--;
   w[w_id].served++;
   w[c[c_id].w_id].cap_cur+=c[c_id].demand;
   w[w_id].cap_cur-=c[c_id].demand;
   c[c_id].w_id=w_id;
   if (best_cost-tot_cost>EPS)
   {
    best_cost=tot_cost;
    //cerr << "best_cost=" << best_cost << " c_id=" << c_id << " w_id=" << w_id << " diff=" << diff << endl;
    best=c;
   }
  }
 }
}

void set_random()
{
 for(int i=0;i<m;i++) 
 {
  int a=rand()%n;
  while (w[a].cap_cur<c[i].demand) a=rand()%n;
  c[i].w_id=a;
  w[a].served++;
  w[a].cap_cur-=c[i].demand;
 }
}

void print_output()
{
 cout << best_cost << " " << 0 << endl;
 for(int i=0;i<m;i++) cout << best[i].w_id << " ";
 cout << endl;
}

void solve() {
 srand(time(NULL));
 cout << fixed << setprecision(4);
 cerr << fixed << setprecision(4);
 cin >> n >> m;
 w.resize(n);
 c.resize(m);
 for(int i=0;i<n;i++) cin >> w[i].cost >> w[i].cap_cur >> w[i].lc.x >> w[i].lc.y;
 for(int i=0;i<m;i++) cin >> c[i].demand >> c[i].lc.x >> c[i].lc.y;
 set_random();
 set_tot_distance();
 cerr << "init = " << tot_cost << endl;
 //for(int i=0;i<m;i++) cerr << best[i].w_id << " ";cerr << endl;
 simulated_annealing();
 for(int i=0;i<n;i++) assert(w[i].cap_cur>=0);
 print_output();
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
