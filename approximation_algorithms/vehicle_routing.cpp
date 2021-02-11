// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

#define EPS 1e-9

struct customer
{
 customer() : id(-1), d(0), x(0), y(0) {}
 int id;
 int d;
 double x;
 double y;
};

int n,v,c;
double score=0.0;
vector < vector < double > > dist;
double best_score=DBL_MAX;

struct vehicle
{
 vehicle() : fr(c), sc(0), route({0,0}) {}
 int fr;
 double sc;
 vector < int > route;
};

vector < customer > q,qq;
vector < vehicle > z,best_z;

double distf(int i, int j)
{
 return sqrt((qq[i].x-qq[j].x)*(qq[i].x-qq[j].x)+(qq[i].y-qq[j].y)*(qq[i].y-qq[j].y));
}

double vehicle_score(vehicle g)
{
 double res=0;
 for(unsigned i=1;i<g.route.size();i++) res+=dist[g.route[i]][g.route[i-1]];
 return res;
}

bool is_accepted(const int &diff, const double &temperature)
{
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-0.9>EPS) return true;
 return false;
}

void type_0(const double &temperature)
{
 int vid,idx1,idx2,max_trial=10;
 do
 {
  vid=rand()%v;
 } while(z[vid].route.size()<4 && --max_trial);
 if (max_trial==0) return;
 idx1=1+rand()%(z[vid].route.size()-2);
 do
 {
  idx2=1+rand()%(z[vid].route.size()-2);
 } while(idx1==idx2);
 auto temp_vehicle=z[vid];
 swap(temp_vehicle.route[idx1],temp_vehicle.route[idx2]);
 temp_vehicle.sc=vehicle_score(temp_vehicle);
 if (temp_vehicle.sc<z[vid].sc)
 {
  //D(temp_vehicle.route,z[vid].route,temp_vehicle.sc,z[vid].sc);
  score=score-z[vid].sc+temp_vehicle.sc;
  z[vid]=temp_vehicle;
 }
}

void type_1(const double &temperature)
{
 int vid1,vid2,idx1,idx2,max_trial;
 
 max_trial=10;
 do
 {
  vid1=rand()%v;
  if (--max_trial==0) break;
 } while(z[vid1].route.size()<3);
 if (max_trial==0) return;
 
 max_trial=10;
 do
 {
  do
  {
   vid2=rand()%v;
  } while(vid1==vid2);
  if (--max_trial==0) break;
 } while(z[vid2].route.size()<3);
 if (max_trial==0) return;
 
 assert(vid1!=vid2);
 assert(z[vid1].route.size()>2);
 assert(z[vid2].route.size()>2);
 
 idx1=1+rand()%(z[vid1].route.size()-2);
 idx2=1+rand()%(z[vid2].route.size()-2);

 int tv1_free = z[vid1].fr+qq[z[vid1].route[idx1]].d-qq[z[vid2].route[idx2]].d;
 if (tv1_free<0) return;
 int tv2_free = z[vid2].fr+qq[z[vid2].route[idx2]].d-qq[z[vid1].route[idx1]].d;
 if (tv2_free<0) return;
 
 auto tv1=z[vid1];
 auto tv2=z[vid2];
 
 swap(tv1.route[idx1],tv2.route[idx2]);
 tv1.sc=vehicle_score(tv1);
 tv2.sc=vehicle_score(tv2);
 tv1.fr=tv1_free;
 tv2.fr=tv2_free;
 
 if (is_accepted(z[vid1].sc+z[vid2].sc-tv1.sc-tv2.sc,temperature))
 {
  /*D(z[vid1].route,z[vid2].route);
  D(tv1.route,tv2.route);*/
  //D(z[vid1].sc,z[vid2].sc,tv1.sc,tv2.sc);
  score=score-z[vid1].sc-z[vid2].sc+tv1.sc+tv2.sc;
  z[vid1]=tv1;
  z[vid2]=tv2;
 }
}

void type_2(const double &temperature)
{
 int vid1,vid2,idx1,max_trial;
 
 max_trial=10;
 do
 {
  vid1=rand()%v;
  if (--max_trial==0) break;
 } while(z[vid1].route.size()<3);
 if (max_trial==0) return;
 
 max_trial=10;
 do
 {
  if (--max_trial==0) break;
  vid2=rand()%v;
 } while(vid1==vid2);
 if (max_trial==0) return;
 
 assert(vid1!=vid2);
 assert(z[vid1].route.size()>2);
 
 idx1=1+rand()%(z[vid1].route.size()-2);

 int tv1_free = z[vid1].fr+qq[z[vid1].route[idx1]].d;
 int tv2_free = z[vid2].fr-qq[z[vid1].route[idx1]].d;
 if (tv2_free<0) return;
 
 auto tv1=z[vid1];
 auto tv2=z[vid2];
 
 tv2.route[tv2.route.size()-1]=z[vid1].route[idx1];
 tv2.route.push_back(0);
 tv1.route.erase(tv1.route.begin()+idx1);
 
 tv1.sc=vehicle_score(tv1);
 tv2.sc=vehicle_score(tv2);

 tv1.fr=tv1_free;
 tv2.fr=tv2_free;

 if (is_accepted(z[vid1].sc+z[vid2].sc-tv1.sc-tv2.sc,temperature))
 {
  /*D(z[vid1].route,z[vid2].route);
  D(tv1.route,tv2.route);*/
  //D(z[vid1].sc,z[vid2].sc,tv1.sc,tv2.sc);
  score=score-z[vid1].sc-z[vid2].sc+tv1.sc+tv2.sc;
  z[vid1]=tv1;
  z[vid2]=tv2;
 }
}

void sa()
{
 int restart=100;
 int iter_idx=0;
 while(restart--)
 {
  //z=best_z;
  //score=best_score;
  double temperature=1000;
  while(temperature>EPS)
  {
   if (++iter_idx%100000==0) D(restart,iter_idx,score,best_score);
   int type=rand()%10;
   if (type<8) type_0(temperature);
   else if (type==8) type_1(temperature);
   else if (type==9) type_2(temperature);
   temperature-=0.0001;
   if (score<best_score)
   {
    best_score=score;
    best_z=z;
   }
  }
 }
}

bool sort_01(customer c1, customer c2)
{
 return c1.d>c2.d;
}

void solve(const int &test_id)
{
 cin >> n >> v >> c;
 q.resize(n);
 dist.assign(n, vector < double > (n, 0));
 z.resize(v);
 for(int i=0;i<n;i++)
 {
  q[i].id=i;
  cin >> q[i].d >> q[i].x >> q[i].y;
  if (i==0) q[i].d=INT_MAX;
 }
 qq=q;
 for(auto e:qq) D(e.id,e.d,e.x,e.y);
 sort(q.begin(),q.end(),sort_01);
 for(auto e:q) D(e.id,e.d,e.x,e.y);
 for(int i=0;i<n;i++)
 {
  for(int j=i+1;j<n;j++) dist[i][j]=dist[j][i]=distf(i,j);
 }
 for(int i=1;i<n;i++)
 {
  int tv;
  do
  {
   tv=rand()%v;
  } while(q[i].d>z[tv].fr);
  z[tv].route[ z[tv].route.size() - 1 ] = q[i].id;
  z[tv].route.push_back(0);
  z[tv].fr -= q[i].d;
 }
 for(auto &e:z)
 {
  e.sc=vehicle_score(e);
  score+=e.sc;
 }
 D("init",score);
 for(auto e:z) D(e.fr,e.sc,e.route);
 best_score = score;
 best_z = z;
 
 sa();
 
 D("final",score);
 for(auto e:z) D(e.fr,e.sc,e.route);
 
 D("BEST SCORE",best_score);
 for(auto e:best_z) D(e.fr,e.sc,e.route);
 
 for(auto e:z)
 {
  int check=c;
  for(auto f:e.route) check-=qq[f].d;
  assert(check>=0);
 }
 cout << best_score << " 0" << endl;
 for(auto e:best_z)
 {
  for(auto f:e.route) cout << f << " ";
  cout << endl;
 }
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
