// https://serhatgiydiren.github.io/

#include <bits/stdc++.h>

using namespace std;

int b,u1,u2,c;
vector < int > res;
char r0,r1,r2;
string verdict;
vector < bool > seen;

void print()
{
 for(auto e:res) cout << e;
 cout << flush << endl;
 cin >> verdict;
 assert(verdict=="Y");
}

int s()
{
 for(int i=0;i<b/2;i++) if (res[i]!=-1 && res[i]==res[b-1-i]) return i;
 return -1;
}

int d()
{
 for(int i=0;i<b/2;i++) if (res[i]!=-1 && res[b-1-i]!=-1 && res[i]!=res[b-1-i]) return i;
 return -1;
}

void ut()
{
 u1=s();
 u2=d();
}

char dene(const int &idx)
{
 char ans;
 c++;
 assert(c<151);
 cout << idx << flush << endl;
 cin >> ans;
 return ans;
}

void pack(const int &idx)
{
 r0=dene(idx);
 if (c>10 && c%10==1)
 {
  ut();
  if (u1!=-1)
  {
   r1=dene(u1+1);
   if (res[u1]!=(r1-'0')) for(int j=0;j<b/2;j++)
   {
    if (res[j]!=-1) res[j]=1-res[j];
    if (res[b-1-j]!=-1) res[b-1-j]=1-res[b-1-j];
   }
  }
  if (u2!=-1)
  {
   r2=dene(u2+1);
   if (res[u2]!=(r2-'0')) for(int j=0;j<b/2;j++) swap(res[j],res[b-1-j]);
  }
 }
 if (!seen[idx-1]) res[idx-1]=(r0-'0'),seen[idx-1]=true;
}

void solve(const int &test_id)
{
 c=0;
 res.assign(b,-1);
 seen.assign(b,false);
 for(int i=1;i<=b/2;i++)
 {
  if (c%2) dene(1);
  pack(i),pack(b+1-i);
 }
 print();
}
            
void solve_cases()
{
 int test_cases=1;
 cin >> test_cases >> b;
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
