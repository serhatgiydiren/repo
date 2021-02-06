// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,k,res=INT_MAX;
 cin >> n >> k;
 vector < int > x(n+1);
 for(int i=1;i<n+1;i++) cin >> x[i];
 sort(x.begin(),x.end());
 for(int i=1;i<n+1;i++) x[i]+=x[i-1];
 for(int i=k;i<n+1;i++) res=min(res,(k-1)*(x[i]-x[i-1])-(x[i-1]-x[i-k]));
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
