// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

#define EPS 1e-9

int restart=10;
long long score_curr,score_best=0;
double temperature,thres=0.999999,thres_init=thres;

long long score()
{
 return 1ll;
}

bool is_accepted(const long long &diff)
{
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-thres>EPS) return true;
 return false;
}

void type_0()
{
}

void type_1()
{
}

void optimize()
{
 while(restart--)
 {
  auto score_begin=score_curr;
  temperature=1000;
  while(temperature>EPS)
  {
   int typ=rand()%2;
   if (typ==0) type_0();
   else if (typ==1) type_1();
   temperature-=0.001;
   if (score_curr>score_best+(score_best/100))
   {
    score_best=score_curr;
    //best_teams=all_teams;
   }
  }
  if (score_curr>score_begin)
  {
   thres=thres_init;
  }
  else
  {
   thres=double(990*1000+rand()%(10*1000))/(1000*1000);
  }
 }
}

long long calc_score()
{
 long long total=0;
 //for(int i=0;i<team_id;i++) total+=score(i);;
 return total;
}

/*
bool sort_01(pizza a, pizza b)
{
 return a.in.size()>b.in.size();
}
*/

struct ix
{
 int id;
 int cnt;
 vector < pair < string , int > > st;
};

struct street
{
 int id;
 int bg;
 int ed;
 string nm;
 int ti;
};

struct path
{
 int id;
 int cnt;
 vector < string > names;
};

int d,x,s,v,f;
vector < street > z;
vector < ix > ixs;
vector < path > p;
map < string , int > yogun;
int active_ix=0;

void load_output()
{
 string load;
 cin >> load;
 if (load != "LOAD") return;
}

void read_input()
{
 cin >> d >> x >> s >> v >> f;
 z.resize(s);
 ixs.resize(x);
 for(int i=0;i<x;i++) ixs[i].id=i;
 p.resize(v);
 for(int i=0;i<s;i++)
 {
  z[i].id=i;
  cin >> z[i].bg >> z[i].ed >> z[i].nm >> z[i].ti;
  ixs[z[i].ed].st.push_back({z[i].nm,1});
 }
 for(int i=0;i<v;i++)
 {
  cin >> p[i].cnt;
  p[i].names.resize(p[i].cnt);
  for(int j=0;j<p[i].cnt;j++)
  {
   cin >> p[i].names[j];
   if (j+1<p[i].cnt) yogun[p[i].names[j]]++;
  }
 }
}

void prep()
{
 for(auto &e:ixs)
 {
  e.cnt=e.st.size();
  random_shuffle(e.st.begin(),e.st.end());
  e.second=rand()%d;
  if (e.second==0) e.cnt--;
  if (e.cnt) active_ix++;
 }
}

void print_output()
{
 cout << active_ix << endl;
 for(int i=0;i<x;i++)
 {
  if (ixs[i].cnt==0) continue;
  cout << ixs[i].id << endl;
  cout << ixs[i].cnt << endl;
  for(int j=0;j<(int)ixs[i].st.size();j++) if (ixs[i].st[j].second) cout << ixs[i].st[j].first << " " << ixs[i].st[j].second << endl;
 }
}

void init_score()
{
 score_best = score_curr = calc_score();
 D("INIT SCORE",score_curr);
}

void final_check()
{
 D("OPT SCORE",score_curr);
 D("FINAL SCORE",score_best);
 //if (score_curr>score_best) best_teams=all_teams;
}

void solve(const int &test_id)
{
 read_input();
 prep();
 load_output();
 init_score();
 optimize();
 final_check();
 print_output();
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
