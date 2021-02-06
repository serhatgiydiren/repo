// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 string s;
 cin >> s;
 for(size_t i=1;i<s.size();i++)
 {
  if (s[i]>=s[0])
  {
   s.insert(s.begin(),s[i]);
   s.erase(s.begin()+i+1);
  }
 }
 cout << "Case #" << test_id << ": " << s << endl;
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
