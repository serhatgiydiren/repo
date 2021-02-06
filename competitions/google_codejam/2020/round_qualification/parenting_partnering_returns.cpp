// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

struct block
{
 int start;
 int end;
 int id;
};

bool sorter(const block &b1, const block &b2)
{
 return (b1.start < b2.start || (b1.start==b2.start && b1.end<b2.end));
}

void solve(const int &test_id)
{
 int n;
 bool a=false,b=false,possible=true;
 int a_end=0,b_end=0;
 cin >> n;
 vector < block > x(n);
 vector < int > res(n);
 for(int i=0;i<n;i++) cin >> x[i].start >> x[i].end,x[i].id=i;
 sort(x.begin(),x.end(),sorter);
 for(int i=0;i<n;i++)
 {
  if (x[i].start>=a_end) a=false;
  if (x[i].start>=b_end) b=false;
  if (!a)
  {
   res[x[i].id]=1;
   a_end=x[i].end;
   a=true;
  }
  else if (!b)
  {
   res[x[i].id]=2;
   b_end=x[i].end;
   b=true;
  }
  else
  {
   possible=false;
   break;
  }
 }
 cout << "Case #" << test_id << ": ";
 if (possible) for(int i=0;i<n;i++) cout << (res[i]==1?'C':'J');
 else cout << "IMPOSSIBLE";
 cout << endl;
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
