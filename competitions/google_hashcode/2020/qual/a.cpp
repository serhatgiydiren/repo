#include <bits/stdc++.h>


using namespace std;

struct lib
{
 int id;
 int n;
 int t;
 int m;
 vector < pair < int , int > > bid;
 int max_score;
};

vector < lib > q;

struct book
{
 int sc;
 int id;
};

bool sorter(book b1, book b2)
{
 return (b1.sc>b2.sc);
}

bool sorter_lib(lib l1, lib l2)
{
 return (l1.max_score>l2.max_score);
}

bool sorter_lib_2(lib l1, lib l2)
{
 return (*max_element(l1.bid.begin(),l1.bid.end())<*max_element(l2.bid.begin(),l2.bid.end()));
}

int b,l,d;

vector < int > border;
vector < bool > scanned;

int get_score()
{
 int total=0;
 int passed=0;
 for(int i=0;i<b;i++) scanned[i]=false;
 for(int i=0;i<l;i++)
 {
  passed+=q[i].t;
  int tpassed=0;
  for(int j=0;j<q[i].n;j++)
  {
   if (scanned[q[i].bid[j].second]) continue;
   if (passed+tpassed<d) total+=q[i].bid[j].first;
   scanned[q[i].bid[j].second]=true;
   if ((j+1)%q[i].m==0) tpassed++;
  }
 }
 return total;
}

void solve() {
 srand(time(NULL));
 cin >> b >> l >> d;
 vector < book > p(b);
 border.resize(b);
 scanned.resize(b);
 for(int i=0;i<b;i++)
 {
  p[i].id=i;
  cin >> p[i].sc;
 }
 q.resize(l);
 for(int i=0;i<l;i++)
 {
  q[i].id=i;
  q[i].max_score=0;
  cin >> q[i].n >> q[i].t >> q[i].m;
  q[i].bid.resize(q[i].n);
  for(int j=0;j<q[i].n;j++)
  {
   cin >> q[i].bid[j].second;
   q[i].bid[j].first=p[q[i].bid[j].second].sc;
   q[i].max_score+=q[i].bid[j].first;
  }
  sort(q[i].bid.rbegin(),q[i].bid.rend());
  //for(int j=0;j<q[i].n;j++) cerr << q[i].bid[j].first << " ";cerr << endl;
 }

 sort(p.begin(),p.end(),sorter);
 //for(int i=0;i<b;i++) cerr << i << " " << p[i].id << " " << p[i].sc << endl;
 for(int i=0;i<b;i++) border[p[i].id]=i;
 //for(int i=0;i<b;i++) cerr << i << " " << border[i] << endl;

 //random_shuffle(q.begin(),q.end());
 sort(q.begin(),q.end(),sorter_lib);
 int total=get_score();
 cerr << "total=" << total << endl;

 int iter=300000;
 int log_freq=10000;
 for(int i=0;i<iter;i++)
 {
  if (i%log_freq==0) cerr << "iter=" << i << " " << "score=" << total << endl;
  int idx1=rand()%l;
  int idx2=rand()%l;
  swap(q[idx1],q[idx2]);
  int new_score=get_score();
  if (new_score<total && i%log_freq)
  {
   swap(q[idx1],q[idx2]);
  }
  else
  {
   total=new_score;
   //cerr << "new score=" << new_score << endl;
  }
 }

 vector < bool > scanned(b);
 cout << l << endl;
 for(int i=0;i<l;i++)
 {
  cout << q[i].id << " ";
  vector < int > temp;
  for(int j=0;j<q[i].n;j++)
  {
   if (scanned[q[i].bid[j].second]) continue;
   scanned[q[i].bid[j].second]=true;
   temp.push_back(q[i].bid[j].second);
  }
  cout << temp.size() << endl;
  for(unsigned j=0;j<temp.size();j++) cout << temp[j] << " ";
  if (temp.size()) cout << endl;
 }
 cerr << total << endl;
}

int main() {
 solve();
 return EXIT_SUCCESS;
}
