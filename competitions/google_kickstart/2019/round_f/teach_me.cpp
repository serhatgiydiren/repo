// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

const int M=50005;

vector < int > x[M];

void solve(const int &test_id)
{
 int n,s,q;
 long long res=0;
 cin >> n >> s;
 map < vector < int > , int > um;
 for(int i=0;i<n;i++)
 {
  cin >> q;
  x[i].resize(q);
  for(int &e:x[i]) cin >> e;
  sort(x[i].begin(),x[i].end());
  um[x[i]]++;
 }
 for(int i=0;i<n;i++)
 {
  int c=0;
  int w=(1<<int(x[i].size()));
  for(int j=1;j<w;j++)
  {
   vector < int > t;
   for(int k=0;k<int(x[i].size());k++) if (j & (1<<k)) t.push_back(x[i][k]);
   c+=um[t];
  }
  res+=(n-c);
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
