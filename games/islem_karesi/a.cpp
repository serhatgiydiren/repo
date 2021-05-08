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

void solve(const int &test_id)
{
 for(int a=1;a<10;a++)
 for(int b=1;b<10;b++)
 for(int c=1;c<10;c++)
 for(int d=1;d<10;d++)
 for(int e=1;e<10;e++)
 for(int f=1;f<10;f++)
 for(int g=1;g<10;g++)
 for(int h=1;h<10;h++)
 for(int i=1;i<10;i++)
 {
  if (a + b + c != 24) continue;
  if (d + e + f != 8) continue;
  if (g - h - i != -7) continue;

  if (a * d * g != 42) continue;
  if (b / e * h != 48) continue;
  if (c * f + i != 49) continue;

  D(a,b,c);
  D(d,e,f);
  D(g,h,i);
 }
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
