// IN THE NAME OF GOD
// https://serhatgiydiren.github.io
// 2021/04/22 23:04:17

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

vector < string > x;

string ut()
{
 string pref="",mid="",suf="";
 for(auto s:x)
 {
  string temp="",last="";
  bool star_seen=false;
  for(auto e:s)
  {
   if (e=='*')
   {
    if (!star_seen)
    {
     if (last.size()>pref.size()) swap(last,pref);
     if (pref.substr(0,last.size())!=last) return "*";
     star_seen=true;
    }
    else temp+=last;
    last="";
    continue;
   }
   last+=e;
  }
  if (last.size()>suf.size()) swap(last,suf);
  if (suf.substr(suf.size()-last.size())!=last) return "*";
  mid+=temp;
 }
 return pref+mid+suf;
}

void solve(const int &test_id)
{
 int n;
 cin >> n;
 x.resize(n);
 for(auto &e:x) cin >> e;
 cout << "Case #" << test_id << ": " << ut() << endl;
}

void solve_cases()
{
 int test_cases = 1;
 cin >> test_cases;
 for(int i = 1; i <= test_cases; i++) solve(i);
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

