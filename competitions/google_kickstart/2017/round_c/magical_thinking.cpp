// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,q,c=0,d=0;
 cin >> n >> q;
 vector < string > x(n+1);
 vector < int > y(n);
 for(auto &e:x) cin >> e;
 for(auto &e:y) cin >> e;
 if (n==1)
 {
  for(int i=0;i<q;i++) c+=(x[0][i]==x[n][i]);
  cout << "Case #" << test_id << ": " << min(c,y[0])+(q-c-max(0,y[0]-c)) << endl;
 }
 else
 {
  for(int i=0;i<q;i++) c+=(x[0][i]==x[1][i]);
  for(int i=0;i<q;i++) d+=(x[0][i]==x[1][i] && x[2][i]==x[1][i]);
  int e=(y[0]+y[1]-(q-c))/2;
  int res=c-abs(d-e);
  y[0]-=e;
  y[1]-=e;
  for(int i=0;i<q;i++)
  {
   if (x[0][i]!=x[1][i])
   {
    if (x[0][i]==x[n][i]) { if (y[0]) { res++; y[0]--; } }
    else if (x[1][i]==x[n][i]) { if (y[1]) { res++; y[1]--; } }
    else assert(0==1);
   }
  }
  cout << "Case #" << test_id << ": " << res << endl;
 }
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
