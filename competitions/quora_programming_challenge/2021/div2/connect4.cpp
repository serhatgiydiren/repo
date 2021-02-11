// https://serhatgiydiren.github.io

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) 404
#endif

vector < vector < int > > x;

bool check(const int &t)
{
 for(int i=0;i<6;i++) for(int j=0;j<4;j++) if (x[i][j]==t && x[i][j+1]==x[i][j] && x[i][j+2]==x[i][j] && x[i][j+3]==x[i][j]) return true;
 for(int i=0;i<3;i++) for(int j=0;j<7;j++) if (x[i][j]==t && x[i+1][j]==x[i][j] && x[i+2][j]==x[i][j] && x[i+3][j]==x[i][j]) return true;
 for(int i=0;i<3;i++) for(int j=0;j<4;j++) if (i+3<6 && j+3<7 && x[i][j]==t && x[i+1][j+1]==x[i][j] && x[i+2][j+2]==x[i][j] && x[i+3][j+3]==x[i][j]) return true;
 for(int i=2;i<6;i++) for(int j=3;j<7;j++) if (i+3<6 && j-3>=0 && x[i][j]==t && x[i+1][j-1]==x[i][j] && x[i+2][j-2]==x[i][j] && x[i+3][j-3]==x[i][j]) return true;
 return false;
}

void solve(const int &test_id)
{
 // t=0-> RED, t=1->YELLOW
 int q,t=1;
 x.assign(6, vector < int > (7, 2)); 
 for(int i=1;i<=42;i++)
 {
  t=1-t;
  cin >> q;
  q--;
  for(int j=5;j>=0;j--) if (x[j][q]==2) { x[j][q]=t; break; }
  D("---------------",t,q);
  for(auto e:x) D(e);
  if (check(t))
  {
   if (t==0) cout << "RED " << i << endl;
   else cout << "YELLOW " << i << endl;
   return;
  }
 }
 cout << "DRAW" << endl;
}
            
void solve_cases()
{
 int test_cases=1;
 //cin >> test_cases;
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
