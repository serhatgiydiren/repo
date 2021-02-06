// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

vector < int > x;
int n,k;

bool check(const int &e)
{
 int c=0;
 for(int i=1;i<n;i++) c+=(x[i]-x[i-1]-1)/e;
 return (c<=k);
}

int ut()
{
 int lo=1;
 int hi=int(1e9);
 while(lo<hi)
 {
  int mid=(lo+hi)>>1;
  if (check(mid)) hi=mid;
  else lo=mid+1;
 }
 return hi;
}

void solve(const int &test_id)
{
 cin >> n >> k;
 x.resize(n);
 for(int &a : x) cin >> a;
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
