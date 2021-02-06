#include <bits/stdc++.h>

using namespace std;

struct lib
{
 int id;
 int n;
 int t;
 int m;
 vector < int > bid;
 int c_2;
 int c_3;
};

vector < lib > q;

struct book
{
 int sc;
 vector < int > libs;
};

vector < book > p;

bool sorter_lib(const lib &i1, const lib &i2)
{
 return (i1.n>i2.n);
}

bool sorter_lib_2(const lib &i1, const lib &i2)
{
 return (i1.c_2>i2.c_2 || (i1.c_2==i2.c_2 && i1.c_3>i2.c_3));
}

int b,l,d,best_score,l_final;

int get_score()
{
 int total=0;
 int passed=0;
 vector < bool > seen(b);
 for(int i=0;i<l;i++)
 {
  passed+=q[i].t;
  if (passed>=d) { l_final=i; break; }
  int tpassed=0;
  for(int j=0;j<q[i].n;j++)
  {
   if (seen[q[i].bid[j]]) continue;
   if (passed+tpassed/q[i].m<d)
   {
    total+=p[q[i].bid[j]].sc;
    seen[q[i].bid[j]]=true;
   }
  }
 }
 return total;
}

void solve() {
 int possible_max=0;
 srand(time(NULL));
 cin >> b >> l >> d;
 p.resize(b);
 for(int i=0;i<b;i++)
 {
  cin >> p[i].sc;
  possible_max+=p[i].sc;
 }
 cerr << "possible max=" << possible_max << endl;
 q.resize(l);
 for(int i=0;i<l;i++)
 {
  q[i].id=i;
  q[i].c_2=q[i].c_3=0;
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++)
  {
   cin >> q[i].bid[j];
   p[q[i].bid[j]].libs.push_back(i);
  }
 }
 for(int i=0;i<l;i++) for(int j=0;j<q[i].n;j++) if (p[q[i].bid[j]].libs.size()==2) q[i].c_2++; else q[i].c_3++;
 int min_p_ic=INT_MAX; 
 int max_p_ic=INT_MIN;
 for(int i=0;i<b;i++) max_p_ic=max(max_p_ic,int(p[i].libs.size())),min_p_ic=min(min_p_ic,int(p[i].libs.size()));
 cerr << "min_p_ic=" << min_p_ic << endl;
 cerr << "max_p_ic=" << max_p_ic << endl;

 int min_q_ic=INT_MAX; 
 int max_q_ic=INT_MIN;
 for(int i=0;i<l;i++) max_q_ic=max(max_q_ic,int(q[i].bid.size())),min_q_ic=min(min_q_ic,int(q[i].bid.size()));
 cerr << "min_q_ic=" << min_q_ic << endl;
 cerr << "max_q_ic=" << max_q_ic << endl;

 sort(q.begin(),q.end(),sorter_lib_2);
 best_score=get_score();
 cerr << "init=" << best_score << " l_final=" << l_final << endl;

 vector < bool > seen(b);
 for(int i=0;i<l;i++)
 {
  int curr_total=0;
  int best_idx=i;
  for(int k=0;k<q[i].n;k++) if (!seen[q[i].bid[k]]) curr_total++;
  for(int j=i+1;j<l;j++)
  {
   int temp_total=0;
   for(int k=0;k<q[j].n;k++) if (!seen[q[j].bid[k]]) temp_total++;
   if (temp_total>curr_total)
   {
    curr_total=temp_total;
    best_idx=j;
   }
  }
  swap(q[i],q[best_idx]);
  for(int k=0;k<q[i].n;k++) seen[q[i].bid[k]]=true;
 }
 best_score=get_score();
 cerr << "greedy=" << best_score << " l_final=" << l_final << endl;

 for(int i=l_final;i<l;i++)
 {
  cerr << "i=" << i << " q[i].id=" << q[i].id << endl;
  for(int j=0;j<l_final;j++)
  {
   swap(q[i],q[j]);
   int new_score=get_score();
   if (new_score<=best_score)
   {
    swap(q[i],q[j]);
   }
   else if (new_score>best_score)
   {
    //for(unsigned k=0;k<q[i].bid.size();k++) cerr << q[i].bid[k] << " "; cerr << endl;for(unsigned k=0;k<q[j].bid.size();k++) cerr << q[j].bid[k] << " "; cerr << endl;
    best_score=new_score;
    cerr << "new high score=" << best_score << " idx1=" << i << " q[i].id=" << q[i].id << " idx2=" << j << " q[j].id=" << q[j].id << endl;
    break;
   }
  }
 }

 int log_freq=1e4;
 int iter=1e3*log_freq;
 for(int i=1;i<=iter;i++)
 {
  int idx1=rand()%l;
  int idx2=rand()%l;
  swap(q[idx1],q[idx2]);
  int new_score=get_score();
  if (new_score<best_score)
  {
   swap(q[idx1],q[idx2]);
  }
  else if (new_score>best_score)
  {
   best_score=new_score;
   cerr << "new high score=" << best_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << i << endl;
  }
  if (i%log_freq==0) cerr << "iter=" << i << " " << "score=" << best_score << endl;
 }

 cout << l << endl;
 for(int i=0;i<l;i++)
 {
  cout << q[i].id << " " << q[i].n << endl;
  for(int j=0;j<q[i].n;j++) cout << q[i].bid[j] << " ";
  cout << endl;
 }
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
