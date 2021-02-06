// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

const long long M=1000000000;

void solve(const int &test_id)
{
 long long down=1;
 long long right=1;
 string s;
 cin >> s;
 stack < int > cof;
 stack < pair < char , long long > > q;
 map < char , long long > m;
 for(auto e:s)
 {
  if (e=='(') q.push({e,0});
  else if (e==')')
  {
   map < char , long long > temp;
   while(q.top().first>='A' && q.top().first<='Z')
   {
    temp[q.top().first]=(temp[q.top().first]+q.top().second)%M;
    q.pop();
   }
   q.pop();
   auto c=cof.top();
   cof.pop();
   for(auto &z:temp) z.second=(z.second*c)%M;
   for(auto z:temp) q.push({z.first,z.second});
  }
  else if (e>='2' && e<='9') cof.push(e-'0');
  else q.push({e,1});
 }
 while(!q.empty())
 {
  auto f=q.top();
  q.pop();
  if (f.first=='S') down=(down+f.second)%M;
  else if (f.first=='N') down=(M+down-f.second)%M;
  else if (f.first=='E') right=(right+f.second)%M;
  else if (f.first=='W') right=(M+right-f.second)%M;
 }
 if (down==0) down=M;
 if (right==0) right=M;
 cout << "Case #" << test_id << ": " << right << " " << down << endl;
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
