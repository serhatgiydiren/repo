#include <bits/stdc++.h>

using namespace std;

#define EPS 1e-9

struct lib
{
 int id;
 int n;
 int t;
 int m;
 int max_cap;
 int cur_cap;
 vector < int > bid;
 int possible_max;
 map < int , int > bid_selected;
};

vector < lib > q;

struct book
{
 int id;
 int sc;
 vector < int > lid;
};

vector < book > p;

int b,l,d,l_final,total;

vector < int > border;

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
    total+=p[border[q[i].bid[j]]].sc;
    scanned[q[i].bid[j]]=true;
   }
   else break;
  }
 }
 return total;
}

bool sorter_book(const book &i1, const book &i2)
{
 return(i1.sc>i2.sc);
}

bool sorter_lib(const lib &i1, const lib &i2)
{
 return ( (i1.t<i2.t) || (i1.t==i2.t && i1.possible_max>i2.possible_max));
}

bool sorter_lib_init(const lib &i1, const lib &i2)
{
 return (i1.id<i2.id);
}

bool sorter_lib_book(const int &i1, const int &i2)
{
 return(p[border[i1]].sc>p[border[i2]].sc);
}

bool sorter_lib_book_2(const int &i1, const int &i2)
{
 return(p[i1].sc>p[i2].sc);
}

bool is_accepted(const int &diff, const double &temperature)
{
 if (diff>0) return true;
 if (exp(double(diff)/temperature)-0.9999>EPS) return true;
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
  {
   if (new_score>total) cerr << "OUTER SWAP high score=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << " l_final=" << l_final << endl;
   else if (new_score<total) cerr << "OUTER SWAP LOSS=" << new_score << " idx1=" << idx1 << " idx2=" << idx2 << " iter=" << temperature << " l_final=" << l_final << endl;
   total=new_score;
  }
  else swap(q[idx1],q[idx2]);

  idx1=rand()%l_final;
  idx2=rand()%q[idx1].n;
  idx3=idx2+rand()%(q[idx1].n-idx2);
  swap(q[idx1].bid[idx2],q[idx1].bid[idx3]);
  new_score=get_score();
  if (is_accepted(new_score-total,temperature))
  {
   if (new_score>total) cerr << "INNER SWAP high score=" << new_score << " idxs=" << idx1 << "-" << idx2 << "-" << idx3 << " iter=" << temperature << " l_final=" << l_final << endl;
   else if (new_score<total) cerr << "INNER SWAP LOSS=" << new_score << " idxs=" << idx1 << "-" << idx2 << "-" << idx3 << " iter=" << temperature << " l_final=" << l_final << endl;
   total=new_score;
  }
  else swap(q[idx1].bid[idx2],q[idx1].bid[idx3]);
  temperature-=0.001;
 }
}

void solve() {
 srand(time(NULL));
 cin >> b >> l >> d;
 p.resize(b);
 border.resize(b);
 for(int i=0;i<b;i++)
 {
  p[i].id=i;
  cin >> p[i].sc;
 }
 for(int i=0;i<b;i++) border[p[i].id]=i;
 q.resize(l);
 for(int i=0;i<l;i++)
 {
  q[i].id=i;
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++)
  {
   cin >> q[i].bid[j];
   p[q[i].bid[j]].lid.push_back(i);
  }
  sort(q[i].bid.begin(),q[i].bid.end(),sorter_lib_book_2);
  for(int j=0;j<min(q[i].n,q[i].m*(d-q[i].t));j++) q[i].possible_max+=p[q[i].bid[j]].sc;
 }
 sort(q.begin(),q.end(),sorter_lib);

 int d_temp=d;
 for(int i=0;i<l;i++)
 {
  d_temp-=q[i].t;
  q[i].cur_cap=q[i].max_cap=min(d_temp*q[i].m,q[i].n);
 }

 total=get_score();
 cerr << "init=" << total << endl;

 sort(q.begin(),q.end(),sorter_lib_init);

 sort(p.begin(),p.end(),sorter_book);
 cerr << "here .... 01 " << endl;
 cerr << "here .... 02 " << endl;
 for(int i=0;i<b;i++) border[p[i].id]=i;
 cerr << "here .... 03 " << endl;
 vector < int > lib_order;
 cerr << "here .... 04 " << endl;
 for(int i=0;i<b;i++)
 {
  //cerr << p[i].id << " " << p[i].sc << " " << p[i].lid.size() << endl;
  for(unsigned j=0;j<p[i].lid.size();j++)
  {
   int lib_id=p[i].lid[j];
   if (q[lib_id].cur_cap<=0) continue;
   if (q[lib_id].cur_cap==q[lib_id].max_cap) lib_order.push_back(lib_id);
   q[lib_id].cur_cap--;
   q[lib_id].bid_selected[p[i].id]=q[lib_id].max_cap-q[lib_id].cur_cap-1;
   break;
  }
 }
 cerr << "here .... 05, l= " << l << endl;
 for(int i=0;i<l;i++)
 {
  //cerr << "i=" << i << endl;
  for(int j=0;j<q[i].n;j++) if (q[i].bid_selected.find(q[i].bid[j])==q[i].bid_selected.end()) q[i].bid_selected[q[i].bid[j]]=q[i].bid_selected.size();
  for(auto set_item:q[i].bid_selected) q[i].bid[set_item.second]=set_item.first;
  if (q[i].cur_cap==q[i].max_cap) lib_order.push_back(i);
 }
 auto qq=q;
 for(int i=0;i<l;i++) qq[i]=q[lib_order[i]];
 q=qq;

 cerr << "here .... 06 " << endl;

 total=get_score();
 cerr << "after max flow=" << total << endl;
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
   //cerr << "here 01.... " << i << " " << j << endl;
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

 cerr << "final score=" << total << endl;
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
