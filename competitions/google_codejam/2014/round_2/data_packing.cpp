// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,x,res=0;
 cin >> n >> x;
 priority_queue < int > pq;
 vector < int > y(n);
 for(int &q:y) cin >> q;
 sort(y.rbegin(),y.rend());
 for(int q:y)
 {
  if (pq.empty()) { if (x-q) pq.push(x-q); res++; }
  else
  {
   if (pq.top()>=q) pq.pop();
   else { if (x-q) pq.push(x-q); res++; }
  }
 }
 cout << "Case #" << test_id << ": " << res << endl;
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
