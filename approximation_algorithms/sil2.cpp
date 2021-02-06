#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9

struct lib
{
 int id;
 int n;
 int t;
 int m;
 vector < int > bid;
};

vector < lib > q;

struct book
{
 int sc;
};

vector < book > p;

int b,l,d,best_score;


int get_score()
{
 int total=0;
 int passed=0;
 vector < bool > scanned(b);
 for(int i=0;i<l;i++)
 {
  passed+=q[i].t;
  if (passed>=d) break;
  int tpassed=0;
  for(int j=0;j<q[i].n;j++)
  {
   if (scanned[q[i].bid[j]]) continue;
   if (passed+tpassed/q[i].m<d)
   {
    tpassed++;
    total+=p[q[i].bid[j]].sc;
    scanned[q[i].bid[j]]=true;
   }
   else break;
  }
 }
 return total;
}

bool is_accepted(const int &diff, const double &temperature)
{
 if (diff>=0) return true;
 //if (exp(double(diff)/temperature)-0.99>EPS) return true;
 if (diff==-65 && rand()%10000==0) return true;
 return false;
}

void simulated_annealing()
{
 double temperature=10000;
 int idx1,idx2,new_score;
 while(temperature>EPS)
 {
  int idx1=rand()%l;
  int idx2=rand()%l;
  swap(q[idx1],q[idx2]);
  int new_score=get_score();

  if (is_accepted(new_score-best_score,temperature))
  {
   if (new_score>best_score) cerr << "new high score=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << endl;
   else if (new_score<best_score) cerr << "swap LOSS=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << endl;
   best_score=new_score;
  }
  else swap(q[idx1],q[idx2]);

  temperature-=0.01;
 }
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
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++) cin >> q[i].bid[j];
 }

 /*
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
 */

 int dummy;
 cin >> dummy;
 vector < int > id(l);
 for(int i=0;i<l;i++)
 {
  cin >> id[i];
  cin >> dummy;
  for(int j=0;j<q[id[i]].n;j++) cin >> q[id[i]].bid[j];
 }
 auto qq=q;
 for(int i=0;i<l;i++) qq[i]=q[id[i]];
 q=qq;

 best_score=get_score();
 cerr << "init score=" << best_score << endl;

 simulated_annealing();

 cout << l << endl;
 int passed=0;
 vector < bool > scanned(b);
 for(int i=0;i<l;i++)
 {
  passed+=q[i].t;
  int tpassed=0;
  cout << q[i].id << " " << q[i].n << endl;
  vector < int > temp;
  for(int j=0;j<q[i].n;j++)
  {
   if (scanned[q[i].bid[j]])
   {
    temp.push_back(q[i].bid[j]);
    continue;
   }
   if (passed+tpassed/q[i].m<d)
   {
    tpassed++;
    scanned[q[i].bid[j]]=true;
    cout << q[i].bid[j] << " ";
   }
   else temp.push_back(q[i].bid[j]);
  }
  for(unsigned j=0;j<temp.size();j++) cout << temp[j] << " ";
  cout << endl;
 }

 cerr << "final score=" << best_score << endl;
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
