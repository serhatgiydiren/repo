// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,a=0,b=0,c=0;
 cin >> n;
 vector < vector < int > > x(n, vector < int > (n));
 vector < bool > seen(n+1);
 for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> x[i][j];
 for(int i=0;i<n;i++)
 {
  a+=x[i][i];
  seen.assign(n+1,false); for(int j=0;j<n;j++) if (seen[x[i][j]]) { b++; break; } else seen[x[i][j]]=true;
  seen.assign(n+1,false); for(int j=0;j<n;j++) if (seen[x[j][i]]) { c++; break; } else seen[x[j][i]]=true;
 }
 cout << "Case #" << test_id << ": " << a << " " << b << " " << c << endl;
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
