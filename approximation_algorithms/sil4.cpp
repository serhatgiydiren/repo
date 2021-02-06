#include <bits/stdc++.h>

using namespace std;

struct lib
{
 int id;
 int n;
 int t;
 int m;
 vector < int > bid;
};

vector < lib > q,qq;

struct book
{
 int sc;
 int used;
};

vector < book > p;

int b,l,d,best_score,overall_best;

bool sorter_lib(const lib &i1, const lib &i2)
{
 return (i1.bid.size()>i2.bid.size());
}

void simulated_annealing()
{
 int log_freq=6*1e7;
 int iter=log_freq*5;
 for(int i=1;i<=iter;i++)
 {
  int idx1=rand()%15000;
  int idx2=15000+rand()%(l-15000);
  int diff=0;
  int i1=0,i2=0;
  while(i1<q[idx1].n && i2<q[idx2].n)
  {
   if (q[idx1].bid[i1]<q[idx2].bid[i2])
   {
    if (p[q[idx1].bid[i1]].used==1) diff--;
    i1++;
   }
   else if (q[idx1].bid[i1]>q[idx2].bid[i2])
   {
    if (p[q[idx2].bid[i2]].used==0) diff++;
    i2++;
   }
   else i1++,i2++;
  }
  while(i1<q[idx1].n) { if (p[q[idx1].bid[i1]].used==1) diff--; i1++; }
  while(i2<q[idx2].n) { if (p[q[idx2].bid[i2]].used==0) diff++; i2++; }

  if (diff>=0)
  {
   for(int i=0;i<q[idx1].n;i++) p[q[idx1].bid[i]].used--;
   for(int i=0;i<q[idx2].n;i++) p[q[idx2].bid[i]].used++;
   swap(q[idx1],q[idx2]);
   best_score+=(65*diff);
   if (diff>0) cerr << "new high score=" << best_score << " overall best=" << overall_best << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << i << endl;
   else if (diff<0) cerr << "new LOSS=" << best_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << i << endl;
  }
  if (best_score>overall_best)
  {
   qq=q;
   overall_best=best_score;
   cerr << "********************** " << best_score << endl;
  }
 }
}

void solve() {
 srand(time(NULL));
 cin >> b >> l >> d;
 p.resize(b);
 for(int i=0;i<b;i++) cin >> p[i].sc;
 q.resize(l);
 for(int i=0;i<l;i++)
 {
  q[i].id=i;
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++) cin >> q[i].bid[j];
  sort(q[i].bid.begin(),q[i].bid.end());
 }

 int dummy;
 cin >> dummy;
 vector < int > id(l);
 for(int i=0;i<l;i++)
 {
  cin >> id[i];
  cin >> dummy;
  for(int j=0;j<q[id[i]].n;j++) cin >> q[id[i]].bid[j];
 }
 qq=q;
 for(int i=0;i<l;i++) qq[i]=q[id[i]];
 q=qq;
 for(int i=0;i<l;i++) sort(q[i].bid.begin(),q[i].bid.end());
 sort(q.begin(),q.begin()+15000,sorter_lib);
 qq=q;
 
 for(int i=0;i<b;i++) p[i].used=0;
 for(int i=0;i<15000;i++) for(int j=0;j<q[i].n;j++) p[q[i].bid[j]].used++;
 int used_book=0;
 for(int i=0;i<b;i++) used_book+=(p[i].used>0);
 cerr << used_book << " " << used_book*65 << endl;
 overall_best=best_score=65*used_book;

 for(int k=0;k<10;k++)
 {
  cerr << "step=" << k << endl;
  for(int i=0;i<b;i++) p[i].used=0;
  for(int i=0;i<15000;i++) for(int j=0;j<q[i].n;j++) p[q[i].bid[j]].used++;
  int used_book=0;
  for(int i=0;i<b;i++) used_book+=(p[i].used>0);
  cerr << used_book << " " << used_book*65 << endl;
  best_score=65*used_book;
  simulated_annealing();
  sort(q.begin(),q.begin()+15000,sorter_lib);
 }

 q=qq;
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
