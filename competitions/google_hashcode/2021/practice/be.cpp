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
 set < string > in;
};

struct team
{
 int c;
 vector < int > pid;
 unordered_map < string , int > m;
};

team et;

int m,m_used=0,team_count=0;
vector < int > t(5),t_used(5);
vector < team > all_teams;
vector < pizza > p;
int team_id=0;
long long score_init,score_opt;
map < string , vector < int > > itop;

void add_p_to_t(int pid, int tid)
{
 all_teams[tid].pid.push_back(pid);
 for(auto e:p[pid].in) all_teams[tid].m[e]++;
}

long long score(int idx)
{
 return 1ll*all_teams[idx].m.size()*all_teams[idx].m.size();
}

long long score(team tt)
{
 return 1ll*tt.m.size()*tt.m.size();
}

bool is_accepted(const long long &diff, const double &temperature)
{
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-0.99>EPS) return true;
 return false;
}

vector < int > get_distinct(int n, int c_val)
{
 vector < int > res(n,-1);
 for(int i=0;i<n;i++)
 {
  res[i]=rand()%team_count;
  if (all_teams[res[i]].c!=c_val) { i--; continue; }
  bool found=false;
  for(int j=0;j<i;j++) if (res[j]==res[i]) { found=true; break; }
  if (found) { i--; continue; }
 }
 return res;
}

// old_c = 2, del 4
// new_c = 4, add 2
long long m1(const int &old_c, const int &new_c, const double &temperature)
{
 if (t_used[old_c]<new_c) return 0ll;
 if (t_used[new_c]+old_c>t[new_c]) return 0ll;
 
 vector < int > idx_old = get_distinct(new_c,old_c);
 vector < int > idx_new = get_distinct(old_c,0);
 
 vector < int > all_pizzas;
 for(unsigned i=0;i<idx_old.size();i++) for(auto e:all_teams[idx_old[i]].pid) all_pizzas.push_back(e);
 random_shuffle(all_pizzas.begin(),all_pizzas.end());
 
 for(int i=0;i<old_c;i++)
 {
  all_teams[idx_new[i]].c=new_c;
  for(int j=new_c*i;j<new_c*(i+1);j++) add_p_to_t(all_pizzas[j],idx_new[i]);
 }
 
 long long diff=0ll;
 for(auto e:idx_old) diff-=score(e);
 for(auto e:idx_new) diff+=score(e);
 
 if (is_accepted(diff,temperature))
 {
  for(unsigned i=0;i<idx_old.size();i++) all_teams[idx_old[i]]=et;
  t_used[old_c]-=new_c;
  t_used[new_c]+=old_c;
 }
 else
 {
  diff=0ll;
  for(unsigned i=0;i<idx_new.size();i++) all_teams[idx_new[i]]=et;
 }
 return diff;
}

long long optimize()
{
 if (team_id==1) return 0ll;
 long long total=0;
 for(int i=0;i<100;i++)
 {
  double temperature=1000;
  int iter=0;
  long long diff=0;
  while(temperature>EPS)
  {
   if (++iter%100000==0) D(i,iter,temperature,score_init+total);
   int type=rand()%6;
   if (type==0) diff=m1(2,3,temperature);
   else if (type==1) diff=m1(2,4,temperature);
   else if (type==2) diff=m1(3,2,temperature);
   else if (type==3) diff=m1(3,4,temperature);
   else if (type==4) diff=m1(4,2,temperature);
   else if (type==5) diff=m1(4,3,temperature);
   
   total+=diff;
   //if (diff<0) D("->",diff,iter,temperature,score_init+total);
   temperature-=0.001;
  }
 }
 return total;
}

long long calc_score()
{
 long long total=0;
 for(int i=0;i<team_count;i++) total+=score(i);
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
 team_count=t[2]+t[3]+t[4];
 all_teams.resize(team_count);
 for(int i=0;i<t[4];i++) all_teams[i].c=4;
 for(int i=t[4];i<t[4]+t[3];i++) all_teams[i].c=3;
 for(int i=t[4]+t[3];i<team_count;i++) all_teams[i].c=2;
 //random_shuffle(all_teams.begin(),all_teams.end());
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
 
 for(int i=0;i<m;i++)
 {
  add_p_to_t(p_sorted[i].id, team_id);
  m_used++;
  if ((int)all_teams[team_id].pid.size()==all_teams[team_id].c) t_used[all_teams[team_id].c]++,team_id++;
 }
 for(int j=team_id;j<team_count;j++) all_teams[j].c=0;
 D(m,m_used);
 D(itop.size(),m,t,t_used,team_id,t[2]*2+t[3]*3+t[4]*4,t_used[2]*2+t_used[3]*3+t_used[4]*4);
 cout << team_id << endl;
 score_init = calc_score();
 D(score_init);
 auto diff=optimize();
 D(score_init);
 D(diff);
 D(score_init+diff);
 score_opt = calc_score();
 D(score_opt);
 for(int i=0;i<team_count;i++)
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
