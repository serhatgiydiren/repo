// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,q,a,b,res=0;
 string s;
 cin >> n >> q >> s;
 vector < vector < int > > x(n+1, vector < int > (26));
 for(int i=1;i<n+1;i++)
 {
  x[i]=x[i-1];
  x[i][s[i-1]-'A']++;
 }
 while(q--)
 {
  int oc=0;
  cin >> a >> b;
  for(int i=0;i<26;i++) oc+=((x[b][i]-x[a-1][i])%2==1);
  res+=(oc<=1);
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
