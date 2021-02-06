// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

void solve(const int &test_id)
{
 int a=0;
 string s;
 cin >> s;
 for(int i=0;i<int(s.size());i++)
 {
  if (s[i]>='0' && s[i]<='9')
  {
   int c=(s[i]-'0');
   while(a>c) s.insert(s.begin()+i,')'),a--,i++;
   while(a<c) s.insert(s.begin()+i,'('),a++,i++;
  }
 }
 while(a) s.push_back(')'),a--;
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
