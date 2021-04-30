// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 

#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

class timer:high_resolution_clock
{
 const time_point start_time;
 
 public:
  timer(): start_time(now()) {}
  rep elapsed_time() const { return duration_cast<milliseconds>(now()-start_time).count();} 
};
    
    
mt19937 rng(steady_clock::now().time_since_epoch().count());
uniform_int_distribution distr(1,123456789);

void solve(const int &test_id)
{
 double x=0,y=0;
 for(int i=0;i<1000000;i++) x+=rng();
 for(int i=0;i<1000000;i++) y+=distr(rng);
 vector < int > z(11);
 iota(z.begin(),z.end(),0);
 shuffle(z.begin(),z.end(),rng);
 D(x/1000000,y/1000000,z);
 iota(z.begin(),z.end(),0);
 do {} while(next_permutation(z.begin(),z.end()));
}

void solve_cases()
{
 //int test_cases = 1;
 //cin >> test_cases;
 //for(int i = 1; i <= test_cases; i++) solve(i);
 timer t;
 const int time_limit=1800; // miliseconds
 while (t.elapsed_time() < time_limit) solve(0);
 D(t.elapsed_time());
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
