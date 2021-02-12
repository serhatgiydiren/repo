// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "../debug.h"
#else
#define D(...) 404
#endif

#define EPS 1e-9

struct pizza
{
 int id;
 vector < string > in;
};

struct team
{
 int c;
 int d;
 vector < int > pid;
 map < string , int > m;
};

int m,t2,t3,t4;
vector < team > all_teams,best_teams;
vector < pizza > p;
int team_id=0,restart=50;
long long score_curr,score_best=0;
double temperature,thres=0.999999,thres_init=thres;

long long score(team t)
{
 return 1ll*t.d*t.d;
}

long long score(int all_teams_idx)
{
 return 1ll*all_teams[all_teams_idx].d*all_teams[all_teams_idx].d;
}

void add_p_to_t(int pid, int tid)
{
 all_teams[tid].pid.push_back(pid);
 for(auto e:p[pid].in) if (all_teams[tid].m[e]++==0) all_teams[tid].d++;
}

bool is_accepted(const long long &diff)
{
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-thres>EPS) return true;
 return false;
}

void type_0()
{
 int idx1=rand()%team_id,idx2;
 do idx2=rand()%team_id; while(idx2==idx1);
 int idx1_swap=rand()%all_teams[idx1].c;
 int idx2_swap=rand()%all_teams[idx2].c;
 auto score_old=score(idx1)+score(idx2);

 auto bck1=all_teams[idx1];
 auto bck2=all_teams[idx2];
 
 for(auto e:p[bck1.pid[idx1_swap]].in) if (--bck1.m[e]==0) bck1.d--;
 for(auto e:p[bck2.pid[idx2_swap]].in) if (--bck2.m[e]==0) bck2.d--;
 swap(bck1.pid[idx1_swap],bck2.pid[idx2_swap]);
 for(auto e:p[bck1.pid[idx1_swap]].in) if (bck1.m[e]++==0) bck1.d++;
 for(auto e:p[bck2.pid[idx2_swap]].in) if (bck2.m[e]++==0) bck2.d++;

 auto diff=score(bck1)+score(bck2)-score_old;
 if (is_accepted(diff)) score_curr+=diff,all_teams[idx1]=bck1,all_teams[idx2]=bck2,D(restart,temperature,thres,diff,score_curr,score_best);
}

void optimize()
{
 if (team_id==1) return;
 while(restart--)
 {
  auto score_begin=score_curr;
  temperature=1000;
  while(temperature>EPS)
  {
   type_0();
   temperature-=0.001;
   if (score_curr>score_best+(score_best/100))
   {
    score_best=score_curr;
    best_teams=all_teams;
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
 for(int i=0;i<team_id;i++) total+=score(i);;
 return total;
}

bool sort_01(pizza a, pizza b)
{
 return a.in.size()>b.in.size();
}

void load_output()
{
 string load;
 cin >> load;
 if (load != "LOAD") return;
}

void read_input()
{
 int c;
 string ingredient;
 cin >> m >> t2 >> t3 >> t4;
 p.resize(m);
 for(int i=0;i<m;i++)
 {
  cin >> c;
  while(c--)
  {
   cin >> ingredient;
   p[i].in.push_back(ingredient);
  }
 }
}

void prep()
{
 for(int i=0;i<m;i++) p[i].id=i;
 all_teams.resize(t2+t3+t4);
 for(auto &e:all_teams) assert(e.d==0);
 for(int i=0;i<t4;i++) all_teams[i].c=4;
 for(int i=t4;i<t4+t3;i++) all_teams[i].c=3;
 for(int i=t4+t3;i<t2+t3+t4;i++) all_teams[i].c=2;
 auto p_sorted = p;
 sort(p_sorted.begin(),p_sorted.end(),sort_01);
 for(int i=0;i<m;i++)
 {
  add_p_to_t(p_sorted[i].id, team_id);
  if ((int)all_teams[team_id].pid.size()==all_teams[team_id].c) team_id++;
  if (team_id==(int)all_teams.size()) break;
 }
 D(m,t2+t3+t4,team_id,t2*2+t3*3+t4*4);
}

void print_output()
{
 cout << team_id << endl;
 for(int i=0;i<team_id;i++)
 {
  cout << best_teams[i].c << " ";
  for(auto e:best_teams[i].pid) cout << e << " ";
  cout << endl;
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
 if (score_curr>score_best) best_teams=all_teams;
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
