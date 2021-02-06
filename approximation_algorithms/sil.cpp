#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9

struct lib
{
 int id;
 int n;
 int t;
 int m;
 int possible_max=0;
 vector < int > bid;
};

vector < lib > q;

struct book
{
 int sc;
};

vector < book > p;

bool sorter_lib(const lib &i1, const lib &i2)
{
 return ( (i1.t<i2.t) || (i1.t==i2.t && i1.possible_max>i2.possible_max));
}

bool sorter_bid(const int &i1, const int &i2)
{
 return (p[i1].sc>p[i2].sc);
}

int b,l,d,l_final,total;

int get_score()
{
 int total=0;
 int passed=0;
 vector < bool > scanned(b);
 for(int i=0;i<l;i++)
 {
  passed+=q[i].t;
  if (passed>=d) { l_final=i; break; }
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
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-0.9995>EPS) return true;
 return false;
}

void simulated_annealing()
{
 double temperature=10000;
 int idx1,idx2,idx3,new_score;
 while(temperature>EPS)
 {
  idx1=rand()%l_final;
  idx2=rand()%l;
  if (idx1==idx2) continue;
  swap(q[idx1],q[idx2]);
  new_score=get_score();
  if (is_accepted(new_score-total,temperature))
  //if (new_score>=total)
  {
   if (new_score>total) cerr << "OUTER 1 SWAP high score=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << " l_final=" << l_final << endl;
   else if (new_score<total) cerr << "OUTER 1 SWAP LOSS=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << " l_final=" << l_final << endl;
   total=new_score;
  }
  else swap(q[idx1],q[idx2]);

  idx1=rand()%l_final;
  idx2=rand()%l_final;
  if (idx1==idx2) continue;
  swap(q[idx1],q[idx2]);
  new_score=get_score();
  if (is_accepted(new_score-total,temperature))
  //if (new_score>=total)
  {
   if (new_score>total) cerr << "OUTER 2 SWAP high score=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << " l_final=" << l_final << endl;
   else if (new_score<total) cerr << "OUTER 2 SWAP LOSS=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << " l_final=" << l_final << endl;
   total=new_score;
  }
  else swap(q[idx1],q[idx2]);

  idx1=rand()%l_final;
  idx2=rand()%q[idx1].n;
  idx3=idx2+rand()%(q[idx1].n-idx2);
  swap(q[idx1].bid[idx2],q[idx1].bid[idx3]);
  new_score=get_score();
  if (is_accepted(new_score-total,temperature))
  //if (new_score>=total)
  {
   if (new_score>total) cerr << "INNER SWAP high score=" << new_score << " idxs=" << idx1 << "-" << idx2 << "-" << idx3 << " iter=" << temperature << " l_final=" << l_final << endl;
   else if (new_score<total) cerr << "INNER SWAP LOSS=" << new_score << " idxs=" << idx1 << "-" << idx2 << "-" << idx3 << " iter=" << temperature << " l_final=" << l_final << endl;
   total=new_score;
  }
  else swap(q[idx1].bid[idx2],q[idx1].bid[idx3]);

  temperature-=0.1;
 }
}

void solve() {
 srand(time(NULL));
 cout << fixed << setprecision(6);
 cerr << fixed << setprecision(6);

 cin >> b >> l >> d;
 p.resize(b);
 for(int i=0;i<b;i++)
 {
  cin >> p[i].sc;
 }
 q.resize(l);

 for(int i=0;i<l;i++)
 {
  q[i].id=i;
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++) cin >> q[i].bid[j];
  sort(q[i].bid.begin(),q[i].bid.end(),sorter_bid);
  for(int j=0;j<min(q[i].n,q[i].m*(d-q[i].t));j++) q[i].possible_max+=p[q[i].bid[j]].sc;
 }

 //sort(q.begin(),q.end(),sorter_lib);

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
 total=get_score();
 int start=total;
 cerr << "init=" << total << " l_final=" << l_final << endl;

 for(int cycle=0;cycle<5;cycle++)
 {
  cerr << "cycle = " << cycle << endl;

  for(int i=l_final;i<l;i++) sort(q[i].bid.begin(),q[i].bid.end(),sorter_bid);

  /*for(int i=0;i<l_final;i++)
  {
   auto backup=q[i].bid;
   sort(q[i].bid.begin(),q[i].bid.end(),sorter_bid);
   int temp=get_score();
   if (temp>total)
   {
    cerr << "i=" << i << " new score=" << temp << endl;
    total=temp;
   }
   else if (temp<total) q[i].bid=backup;
  }*/
  
  cerr << "step=";
  for(int step=1;step<=30;step++)
  {
   cerr << step << " ";
   for(int i=0;i<l_final;i++)
   {
    swap(q[i],q[i+step]);
    int temp=get_score();
    if (temp>total)
    {
     cerr << "adjacent outer " << step << " swap i=" << i << " new score=" << temp << endl;
     total=temp;
    }
    else if (temp<total) swap(q[i],q[i+step]);
   }
  }
  cerr << endl;

  simulated_annealing();
 }

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
 cerr << total << "*" << get_score() << endl;
 cerr << "gain = " << total-start << endl;
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
