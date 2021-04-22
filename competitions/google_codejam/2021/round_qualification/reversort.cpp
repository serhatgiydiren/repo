// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/03/26 16:21:30

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

void solve(const int &test_id)
{
 int n,res=0;
 cin >> n;
 vector < int > x(n);
 for(auto &e:x) cin >> e;
 for(int i=0;i<n-1;i++)
 {
  int z=min_element(x.begin()+i,x.end())-x.begin();
  res+=(z+1-i);
  reverse(x.begin()+i,x.begin()+z+1);
 }
 cout << "Case #" << test_id << ": " << res << endl;
}

void solve_cases()
{
 int test_cases = 1;
 cin >> test_cases;
 for(int i = 1; i <= test_cases; i++) solve(i);
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

