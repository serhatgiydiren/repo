// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

const int P=50;
int n;
long long m;
vector < long long > e;

long long ut()
{
 long long res=0;
 vector < vector < int > > x(P, vector < int > (2));
 for(auto q:e) for(int i=P-1;i>=0;i--) x[i][((q & (1ll<<i))>0)]++;
 vector < long long > mv(P+1);
 for(int i=1;i<=P;i++) mv[i]=mv[i-1]+min(x[i-1][0],x[i-1][1])*(1ll<<(i-1));
 for(int i=P-1;i>=0;i--)
 {
  long long cof=(1ll<<i);
  long long slot=max(0ll,m-mv[i]);
  if (slot>=x[i][0]*cof)
  {
   res+=cof;
   m-=x[i][0]*cof;
  }
  else if (slot>=x[i][1]*cof)
  {
   m-=x[i][1]*cof;
  }
  else
  {
   res=-1;
   break;
  }
 }
 return res;
}
            
void solve(const int &test_id)
{
 cin >> n >> m;
 e.resize(n);
 for(auto &f:e) cin >> f;
 cout << "Case #" << test_id << ": " << ut() << endl;
}
            
void solve_cases()
{
 int test_cases=1;
 cin >> test_cases;
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
