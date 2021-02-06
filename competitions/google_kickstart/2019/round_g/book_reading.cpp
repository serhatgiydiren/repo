// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int n,m,q,t;
 long long res=0;
 cin >> n >> m >> q;
 vector < int > torn(n+1);
 for(int i=0;i<m;i++) cin >> t,torn[t]=true;
 vector < int > x(n+1);
 for(int i=1;i<=n;i++) x[i]=n/i;
 for(int i=1;i<=n;i++) for(int j=i;j<=n;j+=i) if (torn[j]) x[i]--;
 for(int i=0;i<q;i++) cin >> t,res+=x[t];
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
