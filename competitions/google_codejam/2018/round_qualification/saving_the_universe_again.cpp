// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

string s;

int eval()
{
 int res=0,c=1;
 for(size_t i=0;i<s.size();i++) { if (s[i]=='S') res+=c; else c*=2; }
 return res;
}

void solve(const int &test_id)
{
 int d,res=0;
 cin >> d >> s;
 for(int i=int(s.size())-2;eval()>d && i>=0;i--)
 {
  if (s[i]=='C' && s[i+1]=='S')
  {
   swap(s[i],s[i+1]);
   i=int(s.size())-1;
   res++;
  }
 }
 if (eval()>d) cout << "Case #" << test_id << ": " << "IMPOSSIBLE" << endl;
 else cout << "Case #" << test_id << ": " << res << endl;
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
