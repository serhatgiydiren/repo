// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

struct sen
{
 int id;
 int count;
};

bool operator<(const sen &s1, const sen &s2)
{
 return (s1.count<s2.count);
}

void solve(const int &test_id)
{
 int n,c;
 priority_queue < sen > pq;
 cin >> n;
 for(int i=0;i<n;i++)
 {
  cin >> c;
  pq.push({i,c});
 }
 cout << "Case #" << test_id << ": ";
 while(!pq.empty())
 {
  sen i1=pq.top();
  pq.pop();
  if (i1.count==1 && pq.size()==2) cout << char('A'+i1.id) << " ";
  else
  {
   sen i2=pq.top();
   pq.pop();
   cout << char('A'+i1.id) << char('A'+i2.id) << " ";
   if (--i1.count) pq.push(i1);
   if (--i2.count) pq.push(i2);
  }
 }
 cout << endl;
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
