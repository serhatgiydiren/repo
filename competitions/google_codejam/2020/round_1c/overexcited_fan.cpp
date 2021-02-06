// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int x,y,res=-1;
 string s;
 cin >> x >> y >> s;
 for(int i=0;i<int(s.size());i++)
 {
  if (s[i]=='N') y++;
  else if (s[i]=='S') y--;
  else if (s[i]=='E') x++;
  else if (s[i]=='W') x--;
  if (abs(x)+abs(y)-i-1<=0) { res=i+1; break; }
 }
 if (res==-1) cout << "Case #" << test_id << ": " << "IMPOSSIBLE" << endl;
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
