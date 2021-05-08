// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/05/01 14:58:06

#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

class timer:high_resolution_clock
{
 const time_point start_time;
 
 public:
  timer(): start_time(now()) {}
  rep elapsed_time() const { return duration_cast<milliseconds>(now()-start_time).count();} 
};

int time_limit=2000;
timer t;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif
    
mt19937 rng(steady_clock::now().time_since_epoch().count());

int n;
vector < vector < vector < int > > > row_cand,col_cand;
vector < int > row_c,col_c;
map < int , int > gemi;

vector < int > parse(vector < int > temp)
{
 vector < int > z;
 int c=0;
 for(auto e:temp)
 {
  if (e==1) c++;
  else
  {
   if (c) z.push_back(c);
   c=0;
  }
 }
 if (c) z.push_back(c);
 return z;
}

vector < int > parse2(vector < int > temp)
{
 vector < int > z(temp.size());
 int c=0;
 for(int i=0;i<(int)temp.size();i++)
 {
  auto e=temp[i];
  if (e==1) c++;
  else
  {
   if (c)
   {
    for(int k=i-c;k<i;k++) z[k]=c;
   }
   c=0;
  }
 }
 if (c) for(int k=n-c;k<n;k++) z[k]=c;
 return z;
}

void read_process(vector < int > &_c,
                  vector < vector < vector < int > > > &_cand,
                  const int &idx)
{
 cin >> _c[idx];
 vector < int > temp(n);
 for(int j=n-_c[idx];j<n;j++) temp[j]=1;
 do
 {
  _cand[idx].push_back(temp);
 } while(next_permutation(temp.begin(),temp.end()));
}

vector < int > dx={1,1,-1,-1};
vector < int > dy={1,-1,1,-1};

void ut(const int &idx=0, vector < vector < int > > ch={})
{
 if (idx==n)
 {
  
  for(int i=0;i<n;i++)
  {
   for(int j=0;j<n;j++)
   {
    if (ch[i][j]==0) continue;
    for(int k=0;k<4;k++)
    {
     int ii=i+dx[k];
     int jj=j+dy[k];
     if (ii>=0 && ii<n && jj>=0 && jj<n && ch[ii][jj]==1) return;
    }
   }
  }
  vector < vector < int > > mat(n, vector < int > (n));
  vector < int > counts(n);
  for(int i=0;i<n;i++)
  {
   vector < int > temp(n);
   for(int j=0;j<n;j++) temp[j]=ch[j][i];
   auto p_0=parse(temp);
   for(auto e:p_0) counts[i]+=e;
   auto p_temp=parse2(temp);
   for(int j=0;j<n;j++) mat[j][i]=max(mat[j][i],p_temp[j]);
   auto p_ch=parse2(ch[i]);
   for(int j=0;j<n;j++) mat[i][j]=max(mat[i][j],p_ch[j]);
  }
  map < int , int > check;
  for(auto e:mat) for(auto f:e) if (f) check[f]++;
  for(auto &e:check) e.second/=e.first;
  if (check==gemi && counts==col_c)
  {
   for(auto e:mat) D(e);
   string res="";
   for(int i=0;i<n;i++)
   {
    for(int j=0;j<n;j++)
    {
     cout << ch[i][j];
     if (i==j)
     {
      if (ch[i][j]) res+="G";
      else res+="B";
     }
    }
    cout << endl;
   }
   D(res);
  }
  return;
 }
 for(auto e:row_cand[idx])
 {
  auto ch_next=ch;
  ch_next.push_back(e);
  ut(idx+1,ch_next);
 }
}

void solve(const int &test_id)
{
 int q,u;
 cin >> n;
 row_cand.resize(n);
 col_cand.resize(n);
 row_c.resize(n);
 col_c.resize(n);
 for(int i=0;i<n;i++) read_process(row_c,row_cand,i);
 for(int i=0;i<n;i++) read_process(col_c,col_cand,i);
 cin >> q;
 while(q--)
 {
  cin >> u;
  gemi[u]++;
 }
 ut();
}

void solve_cases()
{
 int test_cases = 1;
 //cin >> test_cases;
 for(int i = 1; i <= test_cases; i++) { solve(i); D(i,t.elapsed_time()); }
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
