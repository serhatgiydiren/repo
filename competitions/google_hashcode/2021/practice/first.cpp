// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

#define EPS 1e-9

struct pizza
{
 int id;
 set < string > in;
};

struct team
{
 int c;
 vector < int > pid;
 unordered_map < string , int > m;
};

int m,m_used=0;
vector < int > t(5),t_used(5);
vector < team > all_teams;
vector < pizza > p;
int team_id=0;
team unused;
long long score_init,score_opt;
map < string , vector < int > > itop;

long long score(int idx)
{
 return 1ll*all_teams[idx].m.size()*all_teams[idx].m.size();
}

long long score(team tt)
{
 return 1ll*tt.m.size()*tt.m.size();
}

void add_p_to_t(int pid, int tid)
{
 all_teams[tid].pid.push_back(pid);
 for(auto e:p[pid].in) all_teams[tid].m[e]++;
}

bool is_accepted(const long long &diff, const double &temperature)
{
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-0.9>EPS) return true;
 return false;
}

long long m1(int idx1, int idx2)
{
 int idx1_swap,idx2_swap;
 long long score_old,score_new;
 if (idx1>=team_id) score_old = score(idx2);
 else if (idx2>=team_id) score_old = score(idx1);
 else score_old = score(idx1) + score(idx2);

 if (idx1<team_id) idx1_swap=rand()%all_teams[idx1].c;
 else idx1_swap=rand()%unused.c;
 if (idx2<team_id) idx2_swap=rand()%all_teams[idx2].c;
 else idx2_swap=rand()%unused.c;


 if (idx1<team_id) for(auto e:p[all_teams[idx1].pid[idx1_swap]].in) if (--all_teams[idx1].m[e]==0) all_teams[idx1].m.erase(e);
 if (idx2<team_id) for(auto e:p[all_teams[idx2].pid[idx2_swap]].in) if (--all_teams[idx2].m[e]==0) all_teams[idx2].m.erase(e);

 if (idx1>=team_id) swap(unused.pid[idx1_swap],all_teams[idx2].pid[idx2_swap]);
 else if (idx2>=team_id) swap(all_teams[idx1].pid[idx1_swap],unused.pid[idx2_swap]);
 else swap(all_teams[idx1].pid[idx1_swap],all_teams[idx2].pid[idx2_swap]);
 
 if (idx1<team_id) for(auto e:p[all_teams[idx1].pid[idx1_swap]].in) all_teams[idx1].m[e]++;
 if (idx2<team_id) for(auto e:p[all_teams[idx2].pid[idx2_swap]].in) all_teams[idx2].m[e]++;


 if (idx1>=team_id) score_new = score(idx2);
 else if (idx2>=team_id) score_new = score(idx1);
 else score_new = score(idx1) + score(idx2);

 return score_new-score_old;  
}

long long m2(int idx1, int idx2)
{
 if (idx1>=team_id || idx2>=team_id) return LLONG_MIN;
 long long score_old=score(idx1)+score(idx2);

 vector < int > all_pizzas(all_teams[idx1].pid.size()+all_teams[idx2].pid.size());

 for(unsigned i=0;i<all_teams[idx1].pid.size();i++) all_pizzas[i]=all_teams[idx1].pid[i];
 for(unsigned i=0;i<all_teams[idx2].pid.size();i++) all_pizzas[all_teams[idx1].pid.size()+i]=all_teams[idx2].pid[i];

 random_shuffle(all_pizzas.begin(),all_pizzas.end());
 
 all_teams[idx1].m.clear();
 all_teams[idx2].m.clear();

 for(unsigned i=0;i<all_teams[idx1].pid.size();i++)
 {
  all_teams[idx1].pid[i]=all_pizzas[i];
  for(auto e:p[all_teams[idx1].pid[i]].in) all_teams[idx1].m[e]++;
 }

 for(unsigned i=0;i<all_teams[idx2].pid.size();i++)
 {
  all_teams[idx2].pid[i]=all_pizzas[all_teams[idx1].pid.size()+i];
  for(auto e:p[all_teams[idx2].pid[i]].in) all_teams[idx2].m[e]++;
 }

 return score(idx1)+score(idx2)-score_old;  
}

long long optimize()
{
 if (team_id==1) return 0ll;
 double temperature=1000;
 int add=(unused.c*team_id)/(t[2]*2+t[3]*3+t[4]*4),iter=0,idx1,idx2;
 long long diff,total=0;
 D(team_id,add);
 while(temperature>EPS)
 {
  if (++iter%10000==0) D(iter,temperature,total+score_init);
  idx1=rand()%(team_id+add);
  idx2=idx1;
  while(idx2==idx1 || (idx1>=team_id && idx2>=team_id)) idx2=rand()%(team_id+add);

  team bck1,bck2;

  if (idx1<team_id) bck1=all_teams[idx1];
  else bck1=unused;
  if (idx2<team_id) bck2=all_teams[idx2];
  else bck2=unused;
  
  diff=m2(idx1,idx2);
  
  if (is_accepted(diff,temperature))
  {
   if (diff<0) D("->",temperature,diff,score_init+total);
   total+=diff;
  }
  else
  {
   if (idx1<team_id) all_teams[idx1]=bck1;
   else unused=bck1;
   if (idx2<team_id) all_teams[idx2]=bck2;
   else unused=bck2;
  }
  
  temperature-=0.001;
 }
 return total;
}

long long calc_score()
{
 long long total=0;
 for(int i=0;i<team_id;i++) total+=score(i);
 return total;
}

bool sort_01(pizza a, pizza b)
{
 return a.in.size()>b.in.size();
}

bool sort_02(team a, team b)
{
 return score(a)>score(b);
}

void solve(const int &test_id)
{
 int c;
 string ingredient;
 cin >> m >> t[2] >> t[3] >> t[4];
 all_teams.resize(t[2]+t[3]+t[4]);
 for(int i=0;i<t[4];i++) all_teams[i].c=4;
 for(int i=t[4];i<t[4]+t[3];i++) all_teams[i].c=3;
 for(int i=t[4]+t[3];i<t[2]+t[3]+t[4];i++) all_teams[i].c=2;
 p.resize(m);
 for(int i=0;i<m;i++)
 {
  p[i].id=i;
  cin >> c;
  while(c--)
  {
   cin >> ingredient;
   itop[ingredient].push_back(i);
   p[i].in.insert(ingredient);
  }
 }
 auto p_sorted = p;
 sort(p_sorted.begin(),p_sorted.end(),sort_01);
 
 string is_init;
 cin >> is_init;
 if (is_init=="INIT")
 {
  D("seen...");
  vector < bool > seen(m);
  cin >> team_id;
  for(int i=0;i<team_id;i++)
  {
   cin >> all_teams[i].c;
   t_used[all_teams[i].c]++;
   m_used+=all_teams[i].c;
   all_teams[i].pid.resize(all_teams[i].c);
   for(int j=0;j<all_teams[i].c;j++)
   {
    int pid;
    cin >> pid;
    all_teams[i].pid[j]=pid;
    seen[pid]=true;
    for(auto e:p[pid].in) all_teams[i].m[e]++;
   }
  }
  for(int i=0;i<m;i++) if (!seen[i]) unused.pid.push_back(i);
 }
 else
 {
  for(int i=0;i<m;i++)
  {
   if (team_id==(int)all_teams.size()) unused.pid.push_back(p_sorted[i].id);
   else
   {
    add_p_to_t(p_sorted[i].id, team_id);
    m_used++;
    if ((int)all_teams[team_id].pid.size()==all_teams[team_id].c) t_used[all_teams[team_id].c]++,team_id++;
   }
  }
 }
 unused.c=(int)unused.pid.size();
 D(unused.c);
 D(m,m_used);
 D(itop.size(),m,t,t_used,team_id,t[2]*2+t[3]*3+t[4]*4);
 cout << team_id << endl;
 score_init = calc_score();
 D(score_init);
 return;
 auto diff=optimize();
 D(score_init);
 D(diff);
 D(score_init+diff);
 score_opt = calc_score();
 D(score_opt);
 for(int i=0;i<team_id;i++)
 {
  cout << all_teams[i].c << " ";
  for(auto e:all_teams[i].pid) cout << e << " ";
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
